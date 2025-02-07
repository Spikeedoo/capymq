#pragma once

#include "../include/mqueue.h"

// Constants

// 64KB recv buffer
#define RECV_BUFFER_SIZE 65536

// Sizes of different portions of the request protocol
#define REQUEST_TYPE_CHUNK_BYTES 1
#define PAYLOAD_SIZE_CHUNK_BYTES 2

// Enums
typedef enum {
  REQ_TYPE_PUBLISH = 1,
  REQ_TYPE_SUBSCRIBE = 2,
  REQ_TYPE_CREATE = 3,
  REQ_TYPE_DELETE = 4,
  REQ_TYPE_CLOSE = 5,
} REQUEST_TYPE;

// Structs
typedef struct {
  REQUEST_TYPE request_type;
  int payload_size;
  char* payload;
} IncomingRequest;

// Functions
int handle_incoming_message(int client_socket, struct QueueHead *queue, char *buffer);
