/*
   Algorithm 3
   By Josh Perrine
   Each philosopher has their own seat at the table, but they do all of
   their thinking away from the table.  When they get hungry, they try to
   sit at the table, and then picks up their forks
   (first the right and then the left). Allow at most N-1 philosophers to sit
   at the table simultaneously.  When a philosopher is done eating,
   they get up from the table.
   Used A1 code, majority of edits in getForks(int p) and putForks(int p)
   functions, added a Table semephore for philosophers.
   This algorithm does not lead to any deadlock or starvation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"
#include "zemaphore.h"

Zem_t *Fork;
Zem_t *Table;
int N = 0;      //N: number of philosophers
int seats = 0;  //seats: number of seats at table

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

// Picks up fork that philosopher p needs to use
void getForks(int p) {
  // always checks for a seat at the table
  while(1){
    // checks if table is full
    if(seats != 0){
      // philosopher sits at table
      Zem_wait(&Table);

      printf("get: %d\n", p);
      Zem_wait(&Fork[right(p)]);
      Zem_wait(&Fork[left(p)]);

      // should successfully sit down
      seats--;
      return;
    }
  }
}

// Puts fork down that philosopher p is done using
void putForks(int p) {
  printf("put: %d\n", p);

  // philosopher gets up from table
  Zem_post(&Table);
  seats++;

  Zem_post(&Fork[right(p)]);
  Zem_post(&Fork[left(p)]);
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
  seats = N-1;   // set amount of seats to N-1

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

  // initialize table
  // indicates where philosophers will sit while eating
  Table = (Zem_t *)malloc(N * sizeof(Zem_t));
  Zem_init(&Table, 1);

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
