#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, PComparator c = PComparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
  /// Add whatever helper functions and data members you need below
  void trickleUp(int loc);
  void heapify(int idx);
  std::vector<T> items_;
  int ary_;
  PComparator comp;



};

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
{
  ary_ = m;
  comp = c;

}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{

}


template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleUp(int loc)
{
  int parent = (loc-1)/ary_;
  if (parent < 0 || !comp(items_[loc], items_[parent])) //stop if reach root node or if not better than parent
  {
    return;
  }

  else
  {
    std::swap(items_[parent], items_[loc]); //swap with parent
    trickleUp(parent); //trickleup on new location of node which is parent
  }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
  items_.push_back(item);
  trickleUp(items_.size()-1);
}



template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return items_[0];

}

template<typename T, typename PComparator>
void Heap<T, PComparator>::heapify(int idx)
{
  if (((ary_*idx) + 1) >= (int)items_.size()) //if idx node has no child
  {
    return;
  }
  int betterChild = ((ary_*idx) + 1); //assume better child is first child
  for (int i = 2; i <= ary_; i++)
  {
    if (((ary_*idx) + i) < (int)items_.size()) //if another child exists
    {
      int nextChild = ((ary_*idx) + i); //store index of next child
      if (comp(items_[nextChild], items_[betterChild])) //if next child is better
      {
        betterChild = nextChild; //store idx of the next child in better child
      }
    }
  }
  if (comp(items_[betterChild], items_[idx])) //if its better than the current node
  {
    std::swap(items_[idx], items_[betterChild]); //swap them
    heapify(betterChild); //recursively call on new location of value that was previously at idx
  }


}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }

  items_[0] = items_.back();
  items_.pop_back();
  if (!empty())
  {
    heapify(0); 
  }

}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const
{
  return items_.empty();
}



#endif

