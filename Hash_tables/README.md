## HW6
 
 - Name: Andre Pirjanian
 - Email: apirjani@usc.edu

### Programming Problem Notes

  For each programming problem, let us know:

  - How we should compile your code (`g++` command or `make` target)
    Please use the makefile by calling "make".
  - Design decisions you made or other non-trivial choices for your implementation
    My design for the hash table was pretty by the book, I decided to create a private data member numDeleted_
    that would separate the count of the deleted elements of the hash table from the number of items that were
    still in the hash table. 

    For the hash function, I decided to create a helper function called letterDigittoNumber() that takes the input string and a base-36 string. I created another helper function called process() that divides up the input string into substrings of 6 characters and essentially converts the base-36 substring into decimal, filling in the W array. 

    For pairless, I decided to use the hash table that I created, to maintain a THETA(n) runtime. Using a single while loop, I had two conditions: one where we find the pair of the integer we are currently processing, and one where we do not. In the former condition, I either decrement the count of that paired number, or remove it from the hashtable, and also decrement the count of pairless integers. In the latter, I either add the integer to the hashtable, or increment its count, while also incrementing the count of pairless integers.
    
  - Any additional tests you wrote and what files those exist in
    I did not write any additional tests as the ones provided were thorough.
  - Known errors
    Program is passing all the tests thrown at it, no known errors.
  - Anything that might helps us grade (though we will run automated tests), it often does help to know what features may be broken/missing in case we can provide some small partial credit.