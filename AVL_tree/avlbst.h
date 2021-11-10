#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

using namespace std;

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance() const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    AVLNode<Key, Value>* FindInsertLoc(const Key& key) const;
    void insert_fix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* new_node);
    void rotateRight(AVLNode<Key,Value>* node);
    void rotateLeft(AVLNode<Key,Value>* node);
    void remove_fix(AVLNode<Key, Value>* node, char diff);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    if (this->root_ == nullptr) //if tree is empty, just set root to new node
    {
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
        ((AVLNode<Key, Value>*)this->root_)->setBalance(0);
        return;
    }

    AVLNode<Key, Value>* new_node = FindInsertLoc(new_item.first); //finds location to insert or node to replace value

    if (new_node->getKey() == new_item.first) //if key already exists just replace value
    {
        new_node->setValue(new_item.second);
        return;
    }

    
    AVLNode<Key, Value>* insert_thisNode = new AVLNode<Key, Value>(new_item.first, new_item.second, new_node);
    bool addedLeft = false;
    if (new_item.first < new_node->getKey()) //if new node is left child
    {
        new_node->setLeft(insert_thisNode);
        insert_thisNode->setParent(new_node);
        addedLeft = true;
        insert_thisNode->setBalance(0);
    }

    else //if new node is right child
    {
        new_node->setRight(insert_thisNode);
        insert_thisNode->setParent(new_node);
        insert_thisNode->setBalance(0);
    }

    if (new_node->getBalance() == -1 || new_node->getBalance() == 1) //we balanced the node by inserting!
    {
        new_node->setBalance(0);
        return;
    }

    else //if previous balance was 0, we may have messed up the balance of tree
    {
        if (addedLeft)
        {
            new_node->setBalance(-1);
        }

        else
        {
            new_node->setBalance(1);
        }
        insert_fix(new_node, insert_thisNode);
        return;
    }

    
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert_fix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* new_node)
{
    if (parent == nullptr || new_node == nullptr) //base case is when null node gets passed in
    {
        return;
    }

    AVLNode<Key,Value>* grandparent = parent->getParent(); //get parent of parent node
    if (grandparent == nullptr) //check before dereferencing grandparent
    {
        return;
    }
    if (parent == grandparent->getLeft()) //if on left side of grandparent
    {
        grandparent->updateBalance(-1); //add a -1 to balance of grandparent
        if (grandparent->getBalance() == 0) //if we balanced out grandparent by adding node, return!
        {
            return;
        }

        else if (grandparent->getBalance() == -1) //if the grandparent is now left heavy, recurse up to check balance of higher nodes
        {
            insert_fix(grandparent, parent);
        }

        else if (grandparent->getBalance() == -2) //if grandparent's balance is illegal, do rotations
        {
            if (new_node == parent->getLeft()) //if newly inserted node is on left side of parent (zig zig case)
            {
                rotateRight(grandparent); //rotate right
                parent->setBalance(0); grandparent->setBalance(0); 
            }

            else //zig zag case
            {
                rotateLeft(parent); //first rotate left
                rotateRight(grandparent); //then rotate right
                if (new_node->getBalance() == -1) //set balances based on previous balance of new node
                {
                    parent->setBalance(0);
                    grandparent->setBalance(1);
                    new_node->setBalance(0);
                }

                else if (new_node->getBalance() == 0)
                {
                    parent->setBalance(0);
                    grandparent->setBalance(0);
                    new_node->setBalance(0);
                }

                else
                {
                    parent->setBalance(-1);
                    grandparent->setBalance(0);
                    new_node->setBalance(0);
                }

            }
        }

    }

    else //if on right side of grandparent
    {
        grandparent->updateBalance(1); //add 1 to balance of grandparent
        if (grandparent->getBalance() == 0) //if we balanced out grandparent by adding node, return
        {
            return;
        }

        else if (grandparent->getBalance() == 1) //if we made grandparent right heavy, recurse to check higher nodes' balances
        {
            insert_fix(grandparent, parent);
        }

        else if (grandparent->getBalance() == 2) //if illegal balance, do rotations
        {
            if (new_node == parent->getRight()) //zig zig case
            {
                rotateLeft(grandparent);
                parent->setBalance(0); grandparent->setBalance(0);
            }

            else //zig zag case
            {
                rotateRight(parent);
                rotateLeft(grandparent);
                if (new_node->getBalance() == 1) //update balances based on previous balance of added node
                {
                    parent->setBalance(0);
                    grandparent->setBalance(-1);
                    new_node->setBalance(0);
                }

                else if (new_node->getBalance() == 0)
                {
                    parent->setBalance(0);
                    grandparent->setBalance(0);
                    new_node->setBalance(0);
                }

                else
                {
                    parent->setBalance(1);
                    grandparent->setBalance(0);
                    new_node->setBalance(0);
                }

            }
        }

    }

}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node)
{
    AVLNode<Key, Value>* child = node->getLeft();
    AVLNode<Key, Value>* gp = node->getParent();
    if (gp != nullptr)
    {
        if (node == gp->getLeft()) 
        {
            gp->setLeft(child);
        }

        else
        {
            gp->setRight(child);
        }

    }

    else
    {
        this->root_ = child;
    }
    child->setParent(gp);
    node->setLeft(child->getRight());
    if (child->getRight() != nullptr)
    {
        (child->getRight())->setParent(node);
    }
    child->setRight(node);
    node->setParent(child);

}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node)
{
    AVLNode<Key, Value>* child = node->getRight();
    AVLNode<Key, Value>* gp = node->getParent();
    if (gp != nullptr)
    {
        if (node == gp->getLeft())
        {
            gp->setLeft(child);
        }

        else
        {
            gp->setRight(child);
        }

    }

    else
    {
       this->root_ = child; 
    }
    child->setParent(gp);
    node->setRight(child->getLeft());
    if (child->getLeft() != nullptr)
    {
        (child->getLeft())->setParent(node);
    }
    child->setLeft(node);
    node->setParent(child);

}


template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::FindInsertLoc(const Key& key) const
{
    AVLNode<Key, Value>* temp = (AVLNode<Key, Value>*)this->root_;
    while (temp != nullptr) //go until temp is null
    {
        if (key < temp->getKey()) //if less than temp node's key
        {
            if (temp->getLeft() == nullptr) //check if left of temp node is empty
            {
                break; //break out and return temp so we can insert in its empty left spot
            }
            temp = temp->getLeft(); //if its not empty keep going
        }

        else if (key > temp->getKey()) //if greater than temp node's key
        {
            if (temp->getRight() == nullptr) //check if right of temp node is empty
            {
                break; //break out and return temp so we can insert in its empty right spot
            }
            temp = temp->getRight(); //if its not empty keep going
        }

        else
        {
            return temp; //if the key is equal to a key in the tree, return the node so we can replace its value
        }
    }

    return temp;
    
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value>* node = (AVLNode<Key, Value>*)BinarySearchTree<Key, Value>::internalFind(key);
    if (node == nullptr)
    {
        return;
    }
    if (node->getLeft() != nullptr && node->getRight() != nullptr) //node has two children
    {
        AVLNode<Key, Value>* pred = (AVLNode<Key, Value>*)BinarySearchTree<Key, Value>::predecessor(node);
        this->nodeSwap(node, pred);
        if (node == this->root_)
        {
            this->root_ = pred;
        }
    }

    AVLNode<Key, Value>* parent = node->getParent();
    char diff;
    if (parent != nullptr)
    {
        if (node == parent->getLeft())
        {
            diff = 1;
        }

        else
        {
            diff = -1;
        }
    }

    if (node->getLeft() == nullptr && node->getRight() == nullptr) //if its leaf node
    {
        if (parent == nullptr)
        {
            delete node;
            this->root_ = nullptr;
            return;
        }

        if (parent->getLeft() == node) //if on left side of parent
        {
            delete node;
            parent->setLeft(nullptr); //delete and set left child of parent to null
        }

        else
        {
            delete node;
            parent->setRight(nullptr); // delete and set right child of parent to null
        }
    }

    else 
    {
        AVLNode<Key, Value>* childToPromote = nullptr;
        if (node->getLeft() != nullptr) //if it has left child
        {
            childToPromote = node->getLeft(); //store left child
        }

        else //if it has right child
        {
            childToPromote = node->getRight(); //store right child
        }

        if (parent == nullptr) //if root node with one
        {
            delete node;
            childToPromote->setParent(parent);
            this->root_ = childToPromote;
        }
        else if (parent->getLeft() == node) //if on left side of parent
        {
            delete node; //delete node
            parent->setLeft(childToPromote); //set parent's left child to promoted node
            childToPromote->setParent(parent); //set parent of promoted node to parent of deleted node
        }

        else //do same but for right side of parent
        {
            delete node;
            parent->setRight(childToPromote);
            childToPromote->setParent(parent);
        }
    }

    remove_fix(parent, diff);

}

template<class Key, class Value>
void AVLTree<Key, Value>::remove_fix(AVLNode<Key, Value>* node, char diff)
{
    if (node == nullptr)
    {
        return;
    }
    AVLNode<Key, Value>* parent = node->getParent(); //get parent of parent for next recursive call
    char ndiff = diff; //calculate diff for next recursive call
    if (parent != nullptr)
    {
        if (node == parent->getLeft())
        {
            ndiff = 1;
        }

        else
        {
            ndiff = -1;
        }

    }
    if (diff == -1) //if removing from right side
    {
        if ((node->getBalance() + diff) == -2) //if current node becomes out of balance
        {
            AVLNode<Key, Value>* tallChild = node->getLeft(); //get tallest child
            if (tallChild->getBalance() == -1) //zig zig case
            {
                rotateRight(node);
                node->setBalance(0); tallChild->setBalance(0);
                remove_fix(parent, ndiff);
            }

            else if (tallChild->getBalance() == 0) //if tallest child is balanced, rotate right and done!
            {
                rotateRight(node);
                node->setBalance(-1); tallChild->setBalance(1);
            }

            else //zig zag case
            {
                AVLNode<Key, Value>* g = tallChild->getRight(); 
                rotateLeft(tallChild);
                rotateRight(node);
                if (g->getBalance() == 1) //set balances based on grandparent's balance
                {
                    node->setBalance(0);
                    tallChild->setBalance(-1);
                    g->setBalance(0);

                }

                else if (g->getBalance() == 0)
                {
                    node->setBalance(0);
                    tallChild->setBalance(0);
                    g->setBalance(0);
                }

                else
                {
                    node->setBalance(1);
                    tallChild->setBalance(0);
                    g->setBalance(0);

                }
                remove_fix(parent, ndiff);
            }

        }

        else if ((node->getBalance() + diff) == -1) //update balance if doesn't become out of balance
        {
            node->setBalance(-1);
        }

        else 
        {
            node->setBalance(0);
            remove_fix(parent, ndiff);
        }
    }

    else //removing from left side, same thing as above but flipped signs and sides
    {
        if ((node->getBalance() + diff) == 2) 
        {
            AVLNode<Key, Value>* tallChild = node->getRight();
            if (tallChild->getBalance() == 1)
            {
                rotateLeft(node);
                node->setBalance(0); tallChild->setBalance(0);
                remove_fix(parent, ndiff);
            }

            else if (tallChild->getBalance() == 0)
            {
                rotateLeft(node);
                node->setBalance(1); tallChild->setBalance(-1);
            }

            else
            {
                AVLNode<Key, Value>* g = tallChild->getLeft();
                rotateRight(tallChild);
                rotateLeft(node);
                if (g->getBalance() == -1)
                {
                    node->setBalance(0);
                    tallChild->setBalance(1);
                    g->setBalance(0);

                }

                else if (g->getBalance() == 0)
                {
                    node->setBalance(0);
                    tallChild->setBalance(0);
                    g->setBalance(0);
                }

                else
                {
                    node->setBalance(-1);
                    tallChild->setBalance(0);
                    g->setBalance(0);

                }
                remove_fix(parent, ndiff);
            }

        }

        else if ((node->getBalance() + diff) == 1)
        {
            node->setBalance(1);
        }

        else
        {
            node->setBalance(0);
            remove_fix(parent, ndiff);
        }

    }
}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
