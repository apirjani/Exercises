## HW5
 
 - Name: Andre Pirjanian
 - Email: apirjani@usc.edu

### Programming Problem Notes

  For each programming problem, let us know:

  - How we should compile your code (`g++` command or `make` target)
    Please use the makefile by calling "make".
  - Design decisions you made or other non-trivial choices for your implementation
    For gridpaths.cpp, I decided to create a helper function called gridpathsHelper that does the main search. For the parameters, I decided to pass in vector of vectors of XY pairs by reference, along with a vector of XY pairs to build the current path, another vector containing the intermediate and final XY pairs. This last vector allowed me to dynamically switch in between the two goals, which allow the program to behave differently depending on whether we're trying to reach the intermediate coordinate, or the final one. 

    For sat_solver.cpp, I created a base case that evaluated the expression, and returned true if the expression was true. If the expression was false, the function tries the next truth value, and checks the expression's truth value after that. If its true, it returns true. Otherwise, it returns false. The last case, the undecided one, is where the backtracking occurs. If after trying both options don't work, we change the current variable to undecided and change the previous one to the next truth value and try again.
    
  - Any additional tests you wrote and what files those exist in
    I did not write any additional tests as the ones provided were thorough.
  - Known errors
    Program is passing all the tests thrown at it, no known errors.
  - Anything that might helps us grade (though we will run automated tests), it often does help to know what features may be broken/missing in case we can provide some small partial credit.