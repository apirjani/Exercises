## HW3
 
 - Name: Andre Pirjanian
 - Email: apirjani@usc.edu

### Programming Problem Notes

  For each programming problem, let us know:

  - How we should compile your code (`g++` command or `make` target)
    Please use the makefile by calling "make".
  - Design decisions you made or other non-trivial choices for your implementation
    In heap.h, I decided to create two private helper functions, trickleUp and heapify. TickleUp helped with the push public method, as it allowed me to ensure that the newly pushed heapitem would "trickle up" to its appropriate location, maintaing the heap property. The heapify function helped with the pop public method, pop items off the heap while maintaining the heap property. I decided to design trickleUp recursively, which continues to swap the newly added node with its parent until it either reaches the root, or is no longer better than its parent. 
  - Any additional tests you wrote and what files those exist in
    I wrote a very simple test in stack.cpp to test my stack implementation.
  - Known errors
    Program is passing all the tests thrown at it, no known errors.
  - Anything that might helps us grade (though we will run automated tests), it often does help to know what features may be broken/missing in case we can provide some small partial credit.