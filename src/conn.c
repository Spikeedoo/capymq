#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../include/reqproto.h"

void* accept_connection(void *arg) {
  // Parse pthread argument pointer
  int client_socket = *(int *) arg;

  printf("[CapyMQ] Picked up client socket %d on new thread...\n", client_socket);

  // Allocate a recv buffer for this thread's use
  char buffer[RECV_BUFFER_SIZE];
  int bytes_received;

  while (1) {
    bytes_received = handle_incoming_message(client_socket, &buffer[0]);

    // Handle recv error
    if (bytes_received < 0) {
      fprintf(stderr, "[CapyMQ::ERROR] Recv failed for client socket %d\n!", client_socket);
      break;
    }

    // Handle client disconnection
    if (bytes_received == 0) {
      fprintf(stderr, "[CapyMQ] Client socket %d disconnected.\n", client_socket);
      break;
    }
  }

  close(client_socket);
  return NULL;
}
