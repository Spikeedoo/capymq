#pragma once

#include <stdlib.h>
#include <sys/queue.h>

// Structs
struct MessageEntry {
  char *msg; // Dummy data until this gets populated with real stuff
  STAILQ_ENTRY(MessageEntry) entries;
} MessageEntry;

// Call macro to define queue head
STAILQ_HEAD(QueueHead, MessageEntry);

// Functions
struct QueueHead* initialize_message_queue();
int add_queue_message_t(struct QueueHead* queue_ptr, struct MessageEntry* msg_ptr);
struct MessageEntry* pop_queued_message_t(struct QueueHead* queue_ptr);
