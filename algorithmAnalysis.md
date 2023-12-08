# Dining Philosopher's Algorithm Analysis

This is my analysis for project 5's dining philosopher algorithms.

## Algorithm 1

This out of all three of the algorithms was the one I struggled with the most. I think this was the case because the rest of the algorithms all used bits and pieces from this code. At first, I didn't necessarily know where to start. I tried various different things, and I referenced littleOldWoman.c to try to help me get something going. I wasn't getting too far with this, but then I went to check canvas and the module for day 31 or 32 (I don't necessarily remember). I recalled you mentioning something about this, and I found the code for some dinning philosopher programs. I then used these as a basis for how I worked on my algorithms. Then, after getting the main function situated running through some trial and error, I got the algorithm to work. At first, I only used the sleep(int i) function instead of usleep(int i), so I didn't see the deadlock until a couple days later.

## Algorithm 2

For this algorithm, I started off by copying and pasting the code from algorithm 1 and editing its getFork and putFork functions. It is also to mention that I did add some printf lines throughout the process to debug the code. They were usually around when a philosopher would think, eat, get a fork, put a fork, and when they got initialized. For this algorithm, I don't remember having too many struggles. I do remember not knowing how to know when the philosopher got access to both forks, but then I looked it up and found sem_trywait() to use and it worked. So that was good, a philospher was able to get both forks, and if they only got one they put it down. I had some more debugs for this one that I commented or deleted once I figured it out.

## Algorithm 3

For the final algorithm, I did the same thing as for 2... I copied and pasted algorithm 1's code for the base of it. I think this is where I found the usleep(int i) function too (after finishing algorithm 2). I found out that algorithm 1 would go into deadlock and starvation, as it didn't run after a while. And I found that algorithm 2 would not go into any deadlock and starvation as it ran forever. Initially, I made a seat semephore for this algorithm. But I ended up changing it to a Table semephore. I used this by edditing the getForks and putForks functions. I had some struggles because I was doing a seat semephore at first. Using the Table, I had a philosopher wait for a Table to be posted before they went to get their forks. That simulated a philosopher walking to the table. Then I added the philosopher to post the table after they put their forks down in the putFork function. This simulated a philosopher leaving the table. This ended up working and this did not have deadlock or starvation.
