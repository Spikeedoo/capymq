#pragma once

#include <pthread.h>

#include "../include/mqueue.h"

// Structs
typedef struct {
  int client_socket;
  struct QueueHead *queue;
} IncomingConnection;

// Functions
void* accept_connection(void *arg);
