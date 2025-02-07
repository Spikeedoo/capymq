#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/mqueue.h"

void* handle_broker_loop(void *arg) {
  struct QueueHead *queue = *(struct QueueHead **) arg;
  
  while (1) {
    struct MessageEntry *checkOne = pop_queued_message_t(queue);
    if (checkOne) {
      printf("Got something off the queue: %s\n", checkOne->msg);
    } else {
      printf("Nothing on the queue...let's try again...\n");
    }
    free(checkOne);
    sleep(2);
  }

  return NULL;
}
