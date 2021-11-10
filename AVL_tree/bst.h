#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); 
    virtual ~BinarySearchTree(); 
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); 
    virtual void remove(const Key& key); 
    void clear(); //TODO
    bool isBalanced() const; 
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator 
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    

   
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2);

    
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    void clearHelper(Node<Key, Value>* current);
    int getHeight(Node<Key, Value> *current) const;
    bool isBalancedHelper(Node<Key, Value> *current) const;
    void insertHelper(const std::pair<const Key, Value> &keyValuePair, Node<Key, Value>* current);


protected:
    Node<Key, Value>* root_;
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return this->current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return !(*this == rhs);

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    current_ = successor(current_);
    return *this;
}






/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    
    this->clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    if (root_ == nullptr) //if tree is empty
    {
        //create new node with appropriate key-value pair
        Node<Key, Value>* new_node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
        root_ = new_node; //just make root point to new node
        return; //finish function
    }
    insertHelper(keyValuePair, root_);
}

template<class Key, class Value>
void BinarySearchTree<Key, Value>::insertHelper(const std::pair<const Key, Value> &keyValuePair, Node<Key, Value>* current)
{
    if (current == nullptr) //base case is if we reach empty spot in bst
    {
        return;
    }

    else
    {
        if (keyValuePair.first < current->getKey()) //if insert value is less than current node, recurse left
        {
            insertHelper(keyValuePair, current->getLeft()); //recurse left with same keyvaluepair
            if (current->getLeft() == nullptr) //if empty spot in left child of current, insert there
            {
                Node<Key, Value>* new_node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr); //create node to insert
                new_node->setParent(current); //set parent to the current node with empty spot
                current->setLeft(new_node); //set current's left child (which was empty) to new node
            }
        }

        else if (keyValuePair.first > current->getKey()) //if insert value is greater than current node, recurse right
        {
            insertHelper(keyValuePair, current->getRight()); //recurse right with same keyvaluepair
            if (current->getRight() == nullptr) //if empty spot in right child of current, inser there
            {
                Node<Key, Value>* new_node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr); //create node to insert
                new_node->setParent(current); //set parent to the current node with empty spot
                current->setRight(new_node); //set current's right child (which was empty) to new node
            }
        }

        else
        {
            current->setValue(keyValuePair.second); //replace value with new one if keys match
            return;
        }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    
    if (root_ == nullptr) //check for empty tree
    {
        return;
    }

    Node<Key, Value>* temp = internalFind(key);

    if (temp == nullptr) //key doesn't exist in tree
    {
        return;
    }


    if (temp->getLeft() != nullptr && temp->getRight() != nullptr) //node has two children
    {
        Node<Key, Value>* pred = predecessor(temp); 
        nodeSwap(temp, pred); //swap with predecessor
        if (temp == root_)
        {
            root_ = pred;
        }
        
    }

    if (temp->getLeft() == nullptr && temp->getRight() == nullptr) //if its leaf node
    {
        Node<Key, Value>* parent = temp->getParent();
        if (parent == nullptr)
        {
            delete temp;
            root_ = nullptr;
            return;
        }

        if (parent->getLeft() == temp) //if on left side of parent
        {
            delete temp;
            parent->setLeft(nullptr); //delete and set left child of parent to null
        }

        else
        {
            delete temp;
            parent->setRight(nullptr); // delete and set right child of parent to null
        }
    }

    else //if it has one child
    {
        Node<Key, Value>* childToPromote = nullptr;
        if (temp->getLeft() != nullptr) //if it has left child
        {
            childToPromote = temp->getLeft(); //store left child
        }

        else //if it has right child
        {
            childToPromote = temp->getRight(); //store right child
        }
        
        Node<Key, Value>* parent = temp->getParent();

        if (parent == nullptr) //if root node with one
        {
            delete temp;
            childToPromote->setParent(parent);
            root_ = childToPromote;
        }
        else if (parent->getLeft() == temp) //if on left side of parent
        {
            delete temp; //delete node
            parent->setLeft(childToPromote); //set parent's left child to promoted node
            childToPromote->setParent(parent); //set parent of promoted node to parent of deleted node
        }

        else //do same but for right side of parent
        {
            delete temp;
            parent->setRight(childToPromote);
            childToPromote->setParent(parent);
        }

    }

}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    if (current != nullptr)
    {
        if (current->getLeft() == nullptr)
        {
            return nullptr;
        }
        if (current->getLeft() != nullptr)
        {

            Node<Key, Value>* temp = current->getLeft(); //go to left node of current
            while (temp->getRight() != nullptr) //iterate through right of left subtree
            {
                temp = temp->getRight();
            }
            return temp;
        }

    
        else
        {
            Node<Key, Value>* temp = current;
            Node<Key, Value>* parent = temp->getParent();
            while (parent != nullptr) //stop if reach root node
            {
                if (temp == parent->getLeft()) //traverse up ancestor chain of left children
                {
                    temp = parent; //update temp
                    parent = temp->getParent(); //update parent to new temp's parent
                    continue; //jump to top of while loop
                }

                if (temp == parent->getRight()) //if you traverse right child pointer, parent is the predecessor
                {
                    return parent;
                }
            }
        }
        
    }
    

    return current;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO
    if (current != nullptr)
    {
        if (current->getRight() == nullptr)
        {
            return nullptr;
        }
        if (current->getRight() != nullptr) //if right child exists
        {
            Node<Key, Value>* temp = current->getRight(); //go to right node of current
            while (temp->getLeft() != nullptr) //iterate through left of right subtree
            {
                temp = temp->getLeft();
            }
            return temp;
        }

    
        else //if current node has no right child, we must find the node that it is a predecessor to
        {
            Node<Key, Value>* temp = current;
            Node<Key, Value>* parent = temp->getParent();
            while (parent != nullptr) //stop if reach root node
            {
                if (temp == parent->getRight()) //traverse up ancestor chain of right children
                {
                    temp = parent; //update temp
                    parent = temp->getParent(); //update parent to new temp's parent
                    continue; //jump to top of while loop
                }

                if (temp == parent->getLeft()) //if you traverse left child pointer, parent is the successor
                {
                    return parent;
                }
            }

        }
        
    }
    

    return current;
    
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    clearHelper(root_);
    root_ = nullptr;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value>* current)
{
    if (current == nullptr) //base case is called on nullptr
    {
        return;
    }

    else
    {
        clearHelper(current->getLeft()); //first take care of left subtree
        clearHelper(current->getRight()); //then right subtree
        delete current; //then delete current node
        return;
    }
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    Node<Key, Value>* temp = root_; //temporary pointer to continue traversing to left
    while (temp->getLeft() != nullptr) //while there is a left child continue
    {
        temp = temp->getLeft();
    }

    return temp; //this should be the smallest node in tree (since it is leftmost)

}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* temp = root_; //temporary variable to traverse BST
    while (temp != nullptr && temp->getKey() != key) //traverse until you find node with given key
    {
        if (key < temp->getKey()) //if less than current node, go left
        {
            temp = temp->getLeft();
        }

        else //if greater than current node, go right
        {
            temp = temp->getRight();
        }
    }
    if (temp == nullptr) //key not found
    {
        return nullptr;
    }

    else //key found
    {
        return temp;
    }

}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    if (root_ == nullptr) //if tree empty, just return true
    {
        return true;
    }
    return isBalancedHelper(root_); //otherwise call recursive helper

}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::getHeight(Node<Key, Value> *current) const
{
    int heightLeft = 0;
	int heightRight = 0;
	if (current == nullptr) 
	{
		return -1;
	}

	else if (current->getLeft() == nullptr && current->getRight() == nullptr) //if leaf node
	{
		return 0;
	}

	else
	{
		heightLeft = 1 + getHeight(current->getLeft()); //get height of left subtree
		heightRight = 1 + getHeight(current->getRight()); //get height of right subtree
		if (heightLeft > heightRight) //return the taller one
		{
			return heightLeft;
		}

		else
		{
			return heightRight;
		}
	}
}


template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value>* current) const
{
    //Get the heights of the left and right subtrees
	int heightLeft = getHeight(current->getLeft()) + 1; 
	int heightRight = getHeight(current->getRight()) + 1;

    //if the heights are different by more than 1 then its not balanced
	if (abs(heightLeft-heightRight) > 1)
	{
			return false;
	}

	//if this is a leaf node then its balanced
	else if (current->getLeft() == nullptr && current->getRight() == nullptr)
	{
		return true;
	}

	else  // its not a leaf node then 
	{
        bool balanced_right = true; bool balanced_left = true;
        if (current->getRight() != nullptr) 
        {
            balanced_right = isBalancedHelper(current->getRight()); //check if subtree of right child is balanced
        }
        
        if (current->getLeft() != nullptr)
        {
            balanced_left = isBalancedHelper(current->getLeft()); //check if subtree of left child is balanced
        }
        return balanced_right && balanced_left;
		
	}
}





template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Includes print function,
   BinarySearchTree::printRoot().
   Call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
