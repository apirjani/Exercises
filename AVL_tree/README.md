## HW3
 
 - Name: Andre Pirjanian
 - Email: apirjani@usc.edu

### Programming Problem Notes

  For each programming problem, let us know:

  - How we should compile your code (`g++` command or `make` target)
    Please use the makefile by calling "make".
  - Design decisions you made or other non-trivial choices for your implementation
    For the BST class, I decided to create a successor private helper function, which I used to implement the ++ operator for the iterator class. I decided to write insert recursively, using a helper function that would recurse through the BST, finding the first appropriate empty spot to insert the new node into. I also wrote the clear() function recursively, taking advantage of post-order tree traversal to clear out the tree. I call this function in the destructor. 
    
    For the AVLTree class, I wrote a private helper function called FindInsertLoc which returns the parent of the location at which we should insert our new node. I wrote insert_fix, which does the proper balance updates, maintains the balance of the tree, and executes the rotations necessary in order to maintain the balance. I wrote rotateRight and rotateLeft to implement the two types of rotation that the insert_fix function calls. I also wrote remove_fix, which is essentially the remove function's version of insert_fix. 
  - Any additional tests you wrote and what files those exist in
    I did not write any additional tests as the ones provided were thorough.
  - Known errors
    Program is passing all the tests thrown at it, no known errors.
  - Anything that might helps us grade (though we will run automated tests), it often does help to know what features may be broken/missing in case we can provide some small partial credit.