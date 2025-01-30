#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include "../include/conn.h"

// Defaults
#define DEFAULT_PORT 3000
#define DEFAULT_BACKLOG_SIZE 32

// Util to validate port argv input type
int is_int(char str[]) {
  for (int i = 0; str[i] != 0; i++) {
    if (!isdigit(str[i])) {
      return 0;
    }
  }
  return 1;
}

int main(int argc, char *argv[]) {
  // Default port
  int port = DEFAULT_PORT;

  // Backlog size for pending connections
  int backlog_size = DEFAULT_BACKLOG_SIZE;

  // Override default port with first param if possible
  if (argc == 2) {
    if (is_int(argv[1])) {
      port = atoi(argv[1]);
    }
  }

  // Create server socket
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Configure IP Address
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(port);

  // Store size of address data structure
  socklen_t server_address_len = sizeof(server_address);

  // Bind socket to IP
  if (bind(server_socket, (struct sockaddr*) &server_address, server_address_len) < 0) {
    fprintf(stderr, "[CapyMQ::ERROR] Error binding socket on port %d to IP Address!\n", port);
    return 1;
  }

  // Listen to incoming connections over socket
  if (listen(server_socket, backlog_size) < 0) {
    fprintf(stderr, "[CapyMQ::ERROR] Error listening to incoming connections!\n");
    return 1;
  }

  printf("[CapyMQ] Powering on...\n");
  printf("[CapyMQ] Listening for connections on port %d...\n", port);

  // Main connection loop
  while (1) {
    // Client address data structures
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    // Accept a pending connection
    int client_socket = accept(server_socket, (struct sockaddr*) &client_address, &client_address_len);
    if (client_socket < 0) {
      perror("[CapyMQ::ERROR] Connection accept failed...\n");
      continue;
    }

    printf("[CapyMQ] Client connected...passing to thread\n");

    // Spawn a new thread to handle this new connection
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, accept_connection, &client_socket) < 0) {
      perror("[CapyMQ::ERROR] Failed to pass client socket to thread--closing client socket...\n");
      close(client_socket);
      continue;
    }

    // Detach so thread cleans itself up
    pthread_detach(thread_id);
  }
  
  close(server_socket);

  return 0;
}
