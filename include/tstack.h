// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  T data[size];
  int index;

 public:
  TStack() : index(-1) {}

  bool isEmpty() const {
    return index == -1;
  }

  bool isFull() const {
    return index == size - 1;
  }

  void push(T value) {
    if (isFull()) throw "Stack overflow";
    data[++index] = value;
  }

  T pop() {
    if (isEmpty()) throw "Stack Underflow";
    return data[index--];
  }

  T get() const {
    if (isEmpty()) throw "stack is empty";
    return data[index];
  }
};

#endif  // INCLUDE_TSTACK_H_
