#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"
#include "zemaphore.h"

Zem_t *Fork;
int N = 0;  //N: number of philosophers

typedef struct {
  int numLoops;
  int pid;
} arg_t;

// Gets and returns the fork to the left of philosopher p
int left(int p) {
  printf("left: %d\n", p);
  return p;
}

// Gets and returns the fork to the right of philosopher p
int right(int p) {
  printf("right: %d\n", p);
  return ((p+1)%N);
}

// Picks up fork that philosopher p needs to use
void getForks(int p) {
  // checks if its the 0th philosopher at table
  if(p == 0) {
    printf("get: %d\n", p);
    Zem_wait(&Fork[right(p)]);
    Zem_wait(&Fork[left(p)]);
  }
  printf("get: %d\n", p);
  Zem_wait(&Fork[left(p)]);
  Zem_wait(&Fork[right(p)]);
}

// Puts fork down that philosopher p is done using
void putForks(int p) {
  printf("put: %d\n", p);
  Zem_post(&Fork[left(p)]);
  Zem_post(&Fork[right(p)]);
}

// Philosopher thinks
void think() {
  printf("think\n");
  sleep(1);
  return;
}

// Philosopher eats
void eat() {
  printf("eat\n");
  sleep(1);
  return;
}

// What a dining philosopher does
void *philosopher(void *arg) {
  arg_t *args = (arg_t *) arg;
  int p = args->pid;

  for(int i = 0; i < args->numLoops; i++) {
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

  N = atoi(argv[1]);    // get user input into N
  // check if user entered correct number of philosophers
  if(N < 3 || N > 20) {
    printf("number of philosophers must be between 3 and 20\n");
    exit(1);
  }

  // initialize forks
  Zem_t Fork[N];
  for(int i = 0; i < N; i++) {
    Zem_init(&Fork[i], 1);
  }
  printf("There are %d dining philosophers today\n", N);

  printf("dining: started\n");

// NOT WORKING FROM HERE ON OUT

  // initialize philosophers
  pthread_t ph[N];
  arg_t a[N];
  for(int i = 0; i < N; i++) {
    a[i].pid = i;
    a[i].numLoops = 5;
    Pthread_create(&ph[i], NULL, philosopher, &a[i]);
    printf("finishes %d\n", i);
  }

  // joining philosopher threads (i think?)
  for(int i = 0; i < N; i++) {
    Pthread_join(ph[i], NULL);
  }

  printf("dining: finished\n");

  exit(0);
}
