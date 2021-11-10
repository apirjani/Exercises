#ifndef STACK_H
#define STACK_H

/** 
 * Your Stack<T> class must be templated and
 * privately inherit from LList<T>. All
 * operations must run in O(1).
 *
 * Both pop() and top() must throw std::underflow_error
 * if the stack is empty.
 */
#include <stdexcept>
#include "llist.h"

template <typename T>
class Stack : private LList<T> // complete the declaration and implementation  
{
public:
    Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();
    T const & top() const;

};

template <typename T>
Stack<T>::Stack() : LList<T>()
{
}

template <typename T>
bool Stack<T>::empty() const
{
    return LList<T>::empty();
}

template <typename T>
size_t Stack<T>::size() const
{
    return LList<T>::size();
}

template <typename T>
void Stack<T>::push(const T& item)
{
    LList<T>::push_front(item); //use front of list to get O(1) push
}

template <typename T>
void Stack<T>::pop()
{
    LList<T>::remove(0);
}

template <typename T>
T const & Stack<T>::top() const
{
    if (!LList<T>::empty())
    {
        return (*this)[0]; 
    }
    
    else
    {
        throw std::underflow_error("List is empty");
    }
}

#endif
