#include <stdio.h>
#include <sys/socket.h>

#include "../include/reqproto.h"

// Specific handlers
void handle_publish_request(int client_socket, IncomingRequest req) {}
void handle_subscribe_request(int client_socket, IncomingRequest req) {}
void handle_create_request(int client_socket, IncomingRequest req) {}
void handle_delete_request(int client_socket, IncomingRequest req) {}
void handle_close_request(int client_socket, IncomingRequest req) {}

// Incoming request protocol processor
int handle_incoming_message(int client_socket, char *buffer) {
  // Total bytes tracker
  int total_bytes_received = 0;

  // Get chunk for request type
  int bytes_received = recv(client_socket, buffer, REQUEST_TYPE_CHUNK_BYTES, 0);
  if (bytes_received <= 0) return bytes_received;
  total_bytes_received += bytes_received;

  REQUEST_TYPE request_type;
  void (*request_handler_ptr)();

  // Store request type and pointer to handler
  switch (buffer[0]) {
    case REQ_TYPE_PUBLISH:
      request_type = REQ_TYPE_PUBLISH;
      request_handler_ptr = handle_publish_request;
      break;
    
    case REQ_TYPE_SUBSCRIBE:
      request_type = REQ_TYPE_SUBSCRIBE;
      request_handler_ptr = handle_subscribe_request;
      break;

    case REQ_TYPE_CREATE:
      request_type = REQ_TYPE_CREATE;
      request_handler_ptr = handle_create_request;
      break;

    case REQ_TYPE_DELETE:
      request_type = REQ_TYPE_DELETE;
      request_handler_ptr = handle_delete_request;
      break;

    case REQ_TYPE_CLOSE:
      request_type = REQ_TYPE_CLOSE;
      request_handler_ptr = handle_close_request;
      break;

    default:
      printf("[CapyMQ] Invalid request type!\n");
      return -1;
  }
  
  // Get chunk for payload size
  bytes_received = recv(client_socket, buffer, PAYLOAD_SIZE_CHUNK_BYTES, 0);
  if (bytes_received <= 0) return bytes_received;
  total_bytes_received += bytes_received;

  // Store payload size
  uint16_t payload_size = ntohs(* (uint16_t*) buffer);

  // Get payload chunk
  bytes_received = recv(client_socket, buffer, RECV_BUFFER_SIZE, 0);
  if (bytes_received <= 0) return bytes_received;
  total_bytes_received += bytes_received;

  IncomingRequest req;
  req.request_type = request_type;
  req.payload_size = payload_size;
  req.payload = buffer;

  // Call specific handler
  request_handler_ptr(client_socket, req);
  
  return total_bytes_received;
}