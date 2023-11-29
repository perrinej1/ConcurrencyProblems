# Project 5: Concurrency

# Implementing concurrency solutions

Code for this project is provided here (downloads project code).

## Part 1:  The Dining Philosophers
You will write a program which solves the dining philosophers problem using various algorithms.  You are to implement the algorithms, and then analyze them to determine which ones work best, which ones deadlock, which ones cause starvation, etc.

In order to get synchronization, we will use semaphores via the zemaphore implementation of the text.  

littleOldWoman.c is an example using the semaphore library.

### Algorithms
**Algorithm #1:**
Each philosopher picks up first their left fork, and then their right fork. As we discussed in class, this can lead to deadlock and starvation. How often does it happen? How long can the simulation run?

**Algorithm #2:**
A philosopher is allowed to pick up both of her forks together, only if both of them are available. This is similar to the idea Connor suggested about putting a lock around philosophers 0 and 1.

**Algorithm #3:**
Each philosopher has their own seat at the table, but they do all of their thinking away from the table.  When they get hungry, they try to sit at the table, and then picks up their forks (first the right and then the left).  Allow at most N-1 philosophers to sit at the table simultaneously.  When a philosopher is done eating, they get up from the table.

### Implementation Hints
Your program should accept the number N of philosophers and forks as a command line argument.  N can be any value between 3 and 20.  For these algorithms you must keep track of which forks each philosopher wants to pick up.  One way to do this (as we did in class) is to number the philosophers and forks from 0 through N-1.  Philosopher p will want to pick up fork p (to the left) and fork (p+1) % N (to the right).  Each philosopher should be a thread which then runs a procedure called philosopher

You will have to send some arguments to the procedure. See the littleOldWoman example and also the threads-api example from the text.

Each fork should be a semaphore.  Some of the algorithms require additional semaphores.

### Algorithm Analysis
You should run some experiments to analyze the behavior and performance of the different algorithms.  If an algorithm is susceptible to deadlock, try to find suitable parameters (thinking time, eating time, etc.) to demonstrate deadlock.  

You should think about how you might detect starvation, for example by using the pstat structure from project 2, but looking for threads that have been sleeping for a long time (where you get to define what long time means).

Also vary the number of philosophers because sometimes an algorithm may behave differently for an even or odd number of philosophers.

## Part 2: A new concurrency problem
Provide a solution for the following problem.

This past summer I attended a conference where the hotel was far enough away from the venue that we needed to use a shuttle bus to travel between the two places. (Unnecessary aside: the hotel reminded me of a bunker and eventually I remembered it from an episode of Lost and kept looking for the button I should keep pushing to keep the world going.)

Here's how the shuttle service worked:

- Attendees milled about the front entrance, waiting for a shuttle.
- When a shuttle arrived, everyone already waiting was allowed to get on the shuttle. But Woe To Ye who arrived while boarding, because some holier-than-thou organizer would tell us we could not board this shuttle and must wait for the next.
- The shuttles held 30 people, so if there were more people waiting, they would also have to hang out for the next shuttle. (Unnecessary aside: Pokemon Go stops were scattered about, so it wasn't completely useless.)
- When the allowed attendees were onboard, the shuttle headed off.
- Because they have better things to do than wait for us, if a shuttle arrived and no attendees were waiting, the shuttle immediately departed.

Your solution should enforce the constraints above.

### Implementation Hints
Think about the state you want to keep and the places where you need a semaphore:

- It's likely you'll want to keep track of the attendees, so you'll want an integer and a mutex to do that, but you'll probably also need another semaphore so they actually be waiting when the shuttle is not there.
- One way to think about the shuttle is that it is a semaphore initialized to 30. Getting on is a wait and getting off is a post
- How does the shuttle know to go? (This is a little like the Old Woman, it needs to wait for a post from someone.)
- The shuttle gets to the venue and has to dump the passengers. How is that managed?

For ease of implementation, assume for the moment that the shuttle only picks up attendees at one end of the route, and then heads back.
