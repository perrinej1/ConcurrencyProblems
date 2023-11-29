#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"
#include "zemaphore.h"

Zem_t *Fork;
int N = 0;  //N: number of philosophers

// Gets and returns the fork to the left of philosopher p
int left(int p) {
  return p;
}

// Gets and returns the fork to the right of philosopher p
int right(int p) {
  return ((p+1)%N);
}

// Picks up fork that philosopher p needs to use
void getForks(int p) {
  // checks if its the 0th philosopher at table
  if(p == 0) {
    Zem_wait(&Fork[right(p)]);
    Zem_wait(&Fork[left(p)]);
  }
  Zem_wait(&Fork[left(p)]);
  Zem_wait(&Fork[right(p)]);
}

// Puts fork down that philosopher p is done using
void putForks(int p) {
  Zem_post(&Fork[left(p)]);
  Zem_post(&Fork[right(p)]);
}

// Philosopher thinks
void think() {
  sleep(1);
}

// Philosopher eats
void eat() {
  sleep(1);
}

// What a dining philosopher does
void philosopher(int p) {
  think();
  getForks(p);
  eat();
  putForks(p);
}

int main(int argc, char *argv[]) {
  
}
