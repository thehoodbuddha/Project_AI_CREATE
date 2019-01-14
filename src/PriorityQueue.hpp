//
//  PriorityQueue.hpp
//  SearchStrategies
//
//  Created by David Stritzl on 15/11/15.
//
//

#ifndef PriorityQueue_h
#define PriorityQueue_h

#include <set>
#include <type_traits>

template <typename ElementType, typename Compare = std::less<ElementType>>
class PriorityQueue {
  static_assert(std::is_pointer<ElementType>::value,
                "element type should be a pointer type");

 public:
  // returns the top element
  ElementType front() { return *set_.rbegin(); }

  // checks if the container is empty
  bool empty() { return set_.empty(); }

  // inserts element into the front of the queue
  void push(ElementType const& element) { set_.insert(element); }

  // removes top element from the queue
  void pop() { set_.erase(std::next(set_.rbegin()).base()); }

  // erases element from the queue
  void erase(ElementType const& element) { set_.erase(element); }

  //return queue size
  int size() { return set_.size(); }

 private:
  class WrappedCompare {
   public:
    bool operator()(ElementType const& a, ElementType const& b) const {
      bool result = Compare()(a, b);
      bool is_equal = !result && !Compare()(b, a);

      if (!is_equal) {
        return result;
      }

      return std::less<ElementType>()(a, b);
    }
  };

  std::set<ElementType, WrappedCompare> set_;
};

#endif /* PriorityQueue_h */
