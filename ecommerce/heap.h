#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>
#include <functional> //Constructors compare type
#include <vector>
#include <algorithm> //Swap
#include <utility> //Pair

using namespace std;

struct min_heap {
    bool operator()(pair<double, string> lhs, pair<double, string> rhs) {
        return lhs.first < rhs.first;
    }
};

template <typename T, typename Comparator >
class Heap {
 public:

  Heap(int m, Comparator c);


  ~Heap();

  /// Adds an item
  void push(const T& item);


  T const & top() const;


  void pop();


  bool empty() const;

 private:


  vector<T> items_; //Container for data

  int children;

  Comparator comp;

  int size_;

  void trickleUp(int loc); //For rearranging after push function

  void heapify(int idx); //For rearranging after pop function

};


template <typename T, typename Comparator >
Heap<T,Comparator>::Heap(int m, Comparator c) {

comp = c;

children = m;

size_ = 0; 

}

template <typename T, typename Comparator >
Heap<T,Comparator>::~Heap() {

}

template <typename T, typename Comparator>
bool Heap<T,Comparator>::empty() const {

  if (items_.size() < 1) { 

    return true;

  }

  else {

    return false;

  }

}

template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{

  if(empty()){
    throw std::logic_error("Can't top an empty heap");
  }

  else {

    return items_.front();

  }

}

template <typename T, typename Comparator>
void Heap<T,Comparator>::push(const T& item) {
    items_.push_back(item);
    size_++;
    trickleUp(items_.size()-1);
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::trickleUp(int loc) {

    int parent = loc/children; //Gets the location of the parent of the current item
    while(parent >= 0 && comp(items_[loc], items_[parent]) ) { //While the location of the parent is less than or equal to the top item and the current item is smaller than the parent
        swap(items_[loc], items_[parent]); //Swap the current item with the parent
        loc = parent; //Location of current is now the parent's former location
        parent = (loc-children)/children; //New parent of current is parent of former parent
    }
}


template <typename T, typename Comparator>
void Heap<T,Comparator>::pop() {
  if(empty()) {
    throw std::logic_error("can't pop an empty heap");
  }

  else {

    items_[0] = items_.back(); //Newly added item is now the top item
    items_.pop_back(); //Remove the previously top item
    size_--;
    heapify(0); // Calls heapify to rearrange new heap

  }

}

template <typename T, typename Comparator>
void Heap<T,Comparator>::heapify(int idx) {
  if((idx*children)+1 > size_) { //Where the leftmost child of the current item should be

    return; //Returns if item is a leaf node

  }

      int currentChild = (idx*children)+1; // Starts with the leftmost child of the current (left child must exist because heap is complete m-ary tree)

      for (int i = 1; i < children; i++) { //Compare current child against other child (not including itself)

        if(currentChild+1 <= size_) { //If parent has a child right of the current one (works only for complete trees)
            int rightChild = currentChild+i; //Gets position of right child
            if(comp(items_[rightChild], items_[currentChild])) { //If the right child is smaller than the left child
                currentChild = rightChild; //Set the location of the smaller child to be that of the right child
            }
        } //Else smaller child is left child

      }

      if(comp(items_[currentChild], items_[idx])) { //If the parent is greater than the smaller child
          swap(items_[idx], items_[currentChild]); //Swap the parent with the smaller child 
          heapify(currentChild); //Recursively calls heapify on the parent
      }
    
}

#endif