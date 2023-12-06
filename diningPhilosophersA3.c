#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"
#include "zemaphore.h"

Zem_t *Fork;
Zem_t *Seat;    // Seat semaphore for the table and philosophers to sit at
int N = 0;  //N: number of philosophers

// Gets and returns the fork to the left of philosopher p
int left(int p) {
  //printf("left: %d\n", p);
  return p;
}

// Gets and returns the fork to the right of philosopher p
int right(int p) {
  //printf("right: %d\n", p);
  return ((p+1)%N);
}

// maybe want to modify getForks where a philosopher sits before getting a fork?
// Picks up fork that philosopher p needs to use
void getForks(int p) {
  printf("get: %d\n", p);
  Zem_wait(&Fork[left(p)]);
  Zem_wait(&Fork[right(p)]);
}

// maybe have to modify this too
// Puts fork down that philosopher p is done using
void putForks(int p) {
  printf("put: %d\n", p);
  Zem_post(&Fork[left(p)]);
  Zem_post(&Fork[right(p)]);
}

// Philosopher thinks
void think() {
  printf("think\n");
  usleep(10);
  return;
}

// Philosopher eats
void eat() {
  printf("eat\n");
  usleep(10);
  return;
}

// another way could be adding the seats into here?
// What a dining philosopher does
void *philosopher(void *arg) {
  int p = (int) arg;
  for(int i = 0;; i++) {
    think();
    getForks(p);
    eat();
    putForks(p);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  // check if user used diningPhilosophers correctly
  if(argc != 2) {
    printf("usage: diningPhilosophers numberOfPhilosophers\n");
    exit(1);
  }

  N = atoi(argv[1]);

  // check if user entered correct number of philosophers
  if(N < 3 || N > 20) {
    printf("number of philosophers must be between 3 and 20\n");
    exit(1);
  }

  // initialize forks
  Fork = (Zem_t *)malloc(N * sizeof(Zem_t));
  for(int i = 0; i < N; i++) {
    Zem_init(&Fork[i], 1);
  }

  // initialize seats
  Seat = (Zem_t *)malloc(N * sizeof(Zem_t));
  for(int i = 0; i < N; i++) {
    Zem_init(&Fork[i], 1);
  }

  printf("dining: started\n");

  // initialize philosophers
  pthread_t ph[N];
  for(int i = 0; i < N; i++) {
    int p = i;
    Pthread_create(&ph[i], NULL, philosopher, (void *)p);
  }

  // run forever, philosophers always dining
  while(1){}

  printf("dining: finished\n");

  exit(0);
}
