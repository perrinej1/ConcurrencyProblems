/*
  A new concurrency problem (shuttle problem)
  By Josh Perrine
  Attendees milled about the front entrance, waiting for a shuttle. When a
  shuttle arrived, everyone already waiting was allowed to get on the shuttle.
  The shuttles held 30 people, so if there were more people waiting, they
  would also have to hang out for the next shuttle. When the allowed attendees
  were onboard, the shuttle headed off. Because they have better things to do
  than wait for us, if a shuttle arrived and no attendees were waiting,
  the shuttle immediately departed.
  Used littleOldWoman.c as inspiration for the majority of the code.
  I do think this program works as it was intended to.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"
#include "zemaphore.h"

Zem_t emptyBus;
Zem_t fullBus;
Zem_t mutex;
int riders;

// What an attendee does when boarding the shuttle
void attendee(void *arg) {
  int id = (int) arg;
  //printf("attendee started: %d\n", id);

  // infinant loop
  while(1) {
    Zem_wait(&mutex);
    printf("checking if bus full %d\n", id);

    // checks to see if the shuttle is full
    if(riders == 30) {
      Zem_post(&fullBus);       // let shuttle know it can go
      Zem_wait(&emptyBus);      // wait for shuttle to drop off attendees
    }

    // board the shuttle
    riders++;
    Zem_post(&mutex);
    printf("boarding now\n");
    sleep(2);
  }
  return NULL;
}

// What a shuttle does when it gets full with attendees
void shuttle(int R) {
  // infinant loop
  while(1) {
    Zem_wait(&fullBus);     // wait for attendees to fill up shuttle
    printf("bus departure\n");

    riders = R;             // drop off attendees: riders = 0
    sleep(5);

    Zem_post(&emptyBus);    // come back to board more attendees
  }
}

int main(int argc, char *argv[]) {
  // initializing emptyBus
  Zem_init(&emptyBus, 0);

  // initializing fullBus
  Zem_init(&fullBus, 0);

  // initializing mutex
  Zem_init(&mutex, 1);

  riders = 0;

  printf("shuttle begins\n");

  // initialize attendees
  pthread_t a;
  for(int i = 0; i < 30; i++) {
    int at = i;
    Pthread_create(&a, NULL, attendee, (void *)at);
  }

  // call to shuttle function
  shuttle(0);

  // this should never print
  printf("shuttle ends\n");
  return 0;
}
