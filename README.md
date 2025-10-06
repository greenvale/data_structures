# Data Structures

This repository contains my implementations of common data structures in C++, simply for pedagogical purposes.

Here is some information/tests for some of the implementations in this project:

## Dynamic Array

A lightweight templated dynamic array implementation. Behaves similarly to `std::vector`, providing automatic resizing, insertion, removal and search functions. The Dynamic Array is a resizable array that automatically grows or shrinks as elements are added or removed. It is a wrapper over a static array with a fixed length that can change. `T` is the templated class for the array data. Here are some of the member functions:

* `T get(unsigned int ind)` returns the value at a given index `ind`
* `T* getPtr(unsigned int ind)` returns the pointer to the element at a given index `ind`
* `void set(unsigned int ind, const T &val)` sets the value to `val` at a given index `ind`
* `unsigned int length()` returns the number of elements in the array
* `void append(const T &val)` adds element `val` to end of the array
* `void insert(unsigned int ind, const T &val)` inserts `val` at specific index and shifts elements right
* `void removeVal(const T& val)` removes all elements with value `val` from the array
* `void clear()` clears the contents of the array
* `bool contains(const T& val)` returns `true/false` if `val` is/isn't contained in the array
* `DynamicArray<unsigned int> valIndArr(const T& val)` returns an array of indexes where `val` occurs

An important private member variable is `void reallocStaticArray()`. This is called when the underlying array length is changed. For example if elements are added or removed, the array length may be increased or reduced. After this occurs, `reallocStaticArray` will handle this change by copying the data to a larger/smaller static array.

To test the functionality of `DynamicArray`, clone the repository and build the test file in `testing` using

```
g++ testing/dynamic_array.cpp -I ./
./a.out
```


## Binary Search Tree

A binary tree satisfies: each parent has at most two children. A binary search tree (BST) is a binary tree that satisfies the BST invariant. A binary tree satsifies the BST invariant if for every node the left subtree has smaller elements than that node and the right subtree has larger elements than that node. A BST is designed for containing orderable elements that can be searched through efficiently. The time complexity on average for insertion, deletion, removal and search is $\mathcal{O}(\log(n))$ on average but $\mathcal{O}(n)$ in the degenerate case without balancing.

To test the Binary search tree implementation, build and run:

```
g++ testing/bst.cpp -I ./
./a.out
```

## Binary Heap

A binary heap is a binary tree that keeps the smallest or largest value at the top. It is fully balanced, meaning nodes really have one child unless they are in the second-to-last layer. Elements fill left to right on the bottom layer of the tree. When inserting a new element, the `swim` operation is performed which allows this element to climb up based on its value to satisfy the heap property. Similarly the `sink` operation occurs when a value is removed and replaced with another value in the tree, which might not be in the right position.

To test the Binary Heap implementation build the test file and run:

```
g++ testing/binary_heap.cpp -I ./
./a.out
```

## Hash table

A hash table uses the value of the element to determine its index, allowing for fast look-up. This implementation supports both separate chaining and open addressing. Here are some of the features:

- Generic key-value storage (`KeyValPair<T, U>`)
- Functor-based hash and probe functions
- Customizable collision resolution:
  - Separate Chaining
    - Supports multiple data structures via interface classes (e.g., `DynamicArray`, `SinglyLinkedList`)
  - Open Addressing
    - Linear and Quadratic probing supported
- Load factor monitoring and dynamic resizing (open addressing)

To build and test the Hash table implementation in the case of separate chaining, build and run:

```
g++ testing/hashtable.cpp -I ./
./a.out
```