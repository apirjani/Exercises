## HW2
 
 - Name: Andre Pirjanian
 - Email: apirjani@usc.edu

### Programming Problem Notes

  For each programming problem, let us know:

  - How we should compile your code (`g++` command or `make` target)
    Please use the makefile that I have created, by calling "make".
  - Design decisions you made or other non-trivial choices for your implementation
    In twiteng, I created a private helper function called hashTags() to help me with the search function. This helper function populates the hashtag_map data member that I created, which has keys (strings) that are the hashtags in the system, and values which are sets of tweet pointers. The purpose of this was to allow for more efficient searching, since the look up runtime for maps and sets is log(n). I created two more private helper functions, set_union() and set_intersection(), in order to help me with the search function. I used set_union() to help with OR searches, and set_intersection() to help with AND searches. In order to free up all the dynamic memory allocated, I deallocated the memory for User*'s in twiteng.cpp, and deallocated all the tweets in user.cpp.
  - Any additional tests you wrote and what files those exist in
    I did not write any additional tests since provided tests were comprehensive.
  - Known errors
    Program is passing all the tests thrown at it, no known errors.
  - Anything that might helps us grade (though we will run automated tests), it often does help to know what features may be broken/missing in case we can provide some small partial credit.