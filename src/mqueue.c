#include <stdlib.h>
#include <sys/queue.h>
#include <pthread.h>

#include "../include/mqueue.h" 

// Mutex for queue manipulation
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

// Wrapper for STAILQ initialization
// Returns malloc'd pointer
struct QueueHead* initialize_message_queue() {
  struct QueueHead *queue = malloc(sizeof(struct QueueHead));
  STAILQ_INIT(queue);
  return queue;
}

// Wrapper for STAILQ population
int add_queue_message_t(struct QueueHead* queue_ptr, struct MessageEntry* msg_ptr) {
  pthread_mutex_lock(&mtx);
  STAILQ_INSERT_TAIL(queue_ptr, msg_ptr, entries);
  pthread_mutex_unlock(&mtx);
  return 1;
}

// Wrapper for STAILQ consumption
// Frees memory of popped data
// Returns malloc'd pointer to the result
struct MessageEntry* pop_queued_message_t(struct QueueHead* queue_ptr) {
  // Lock mutex
  pthread_mutex_lock(&mtx);

  // Get first in line
  struct MessageEntry *maybe_next_message = STAILQ_FIRST(queue_ptr);

  // First is a null pointer--unlock mutex & return
  if (!maybe_next_message) {
    pthread_mutex_unlock(&mtx);
    return NULL;
  }

  // Placeholder to hold a copy of the first in line to prevent race condition
  struct MessageEntry copy;

  // Copy over value
  copy = *maybe_next_message;

  // Pop off queue
  STAILQ_REMOVE_HEAD(queue_ptr, entries);

  // TODO: Double check this is freeing correctly?
  free(maybe_next_message);

  // Unlock mutex
  pthread_mutex_unlock(&mtx);

  // Allocate memory in heap for copied structure
  struct MessageEntry *safe_copy = malloc(sizeof(struct MessageEntry));
  if (safe_copy) {
    *safe_copy = copy;
  }

  return safe_copy;
}
