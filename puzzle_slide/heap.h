#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>
#include <functional> 
#include <vector>
#include <algorithm> 

using namespace std;

template <typename T, typename Comparator >
class Heap {
 public:

  Heap(int m, Comparator c);

  ~Heap();


  void push(const T& item);

  T const & top() const;

  void pop();

  bool empty() const;

 private:

  int size_;

  vector<T> items_; 

  int children;

  Comparator comp;

  void trickleUp(int loc); 

  void heapify(int idx); 

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

    int parent = (loc-1)/children;
    while(parent >= 0 && comp(items_[loc], items_[parent]) ) { 
        swap(items_[loc], items_[parent]); 
        loc = parent; 
        parent = (loc-1)/children; 
    }
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::pop() {
  if(empty()) {
    throw std::logic_error("can't pop an empty heap");
  }

  else {

    items_[0] = items_.back(); 
    items_.pop_back(); 
    size_--;
    heapify(0); 

  }

}

template <typename T, typename Comparator>
void Heap<T,Comparator>::heapify(int idx) {
  if((idx*children)+1 >= size_) { 

    return; 

  }

      int currentChild = (idx*children)+1; 

      int bestChild = currentChild;

      for (int i = 1; i < children; i++) { 

        if(currentChild+1 < size_) { 
            int rightChild = currentChild+1; 
            if(comp(items_[rightChild], items_[bestChild])) { 
                bestChild = rightChild; 
            }
        } 

        currentChild++;

      }

      if(comp(items_[bestChild], items_[idx])) { 
          swap(items_[bestChild], items_[idx]); 
          heapify(bestChild); 
      }
    
}

#endif