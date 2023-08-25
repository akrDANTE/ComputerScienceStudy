### All About Algorithms

# What are Algorithms?

An algorithm is a **sequence of steps** (preferably well defined) that are going **to solve a problem**.
A problem could be a mathematical, computer science problem, coding question, a daily activity like you brushing your teeth.. anything.
Suppose there is a system which is in a state called 'A'(initial state), we want to take the system into another state called 'B'(desired state). The problem here is how to take system from state 'A' to state 'B', and algorithm is the answer to that problem.

### Example:

#### Problem : Multiply two given numbers.

As we probably know (if you don't, well my condolences to you, good luck out there!) there can be multiple approaches to multiply two numbers.

i) Take the first number and add it second number times.  
ii) Our old fashioned multiplication where we start with unit digit of the number going to most significant digit, multiplying each with powers of 10 and finally adding all the numbers.

As we can see there are multiple approaches(algorithms) to solve the problem, we want which solves the problem faster, the more efficient algorithm.
Now you can say why bother, when we have already found a solution.. we are done. Even though computers are fast, but they are still limited by hardware which are RAM(memory) and CPU(Central Processing Unit). If our algorithm is badly designed, it will either overflow the memory or it will not solve problem before we die(more on this in [analysis of algorithms]()). So we don't want that.

That is why we study and create algorithms to find efficient and elegant solutions to important problems, which give result in reasonable time while running under hardware constraints.
