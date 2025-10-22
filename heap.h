#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
//checking something

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  // Add whatever helper functions and data members you need below
  std::vector<T> heap;
  int dimension;
  PComparator comparison_type;
};

// Add implementation of member functions here


// Constructor
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) {
  dimension = m;
  comparison_type = c;
}

// Destructor
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {

}

// Push an item into the heap
template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
  heap.push_back(item);
  size_t i = heap.size() - 1;
  while (i > 0) {
    T& parent = heap[(i-1) / dimension];
    T& child = heap[i];
    if (comparison_type(child,parent)) {
      std::swap(child,parent);
      i = (i-1) / dimension;
    }
    else {
      break;
    }
  }
  return;
}

// Check if the heap is empty
template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
  return heap.empty();
}

// Return the size of the heap
template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return heap.size();
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap.front();
}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  std::swap(heap.front(), heap.back());
  heap.pop_back();
  size_t i =0;
  size_t new_i = 0;
  while (i < heap.size()) {
    bool has_child = false;
    for (int j = 1; j <=dimension; j++) {
      if ((i*dimension + j) < heap.size())
      {
        if (j==1) {
          new_i = i * dimension + j;
          has_child = true;
        }
        else {
          if (comparison_type(heap[i* dimension + j], heap[new_i])) {
            new_i = i* dimension + j;
          }
        }
      }
      else {
        break;
      }
    }
    if (has_child) {
      if (comparison_type(heap[new_i], heap[i])) {
        std::swap(heap[new_i], heap[i]);
        i = new_i;
      }
      else {
        break;
      }
    }
    else {
      break;
    }
  }
  return;
}

#endif

