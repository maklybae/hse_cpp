#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
  T value{};
  Node *next{nullptr};
};

template <typename T>
class Stack {
 private:
  Node<T> *last_{nullptr};
  int size_ = 0;

 public:
  void Push(T value) {
    auto temp = new Node<T>{value, last_};
    last_ = temp;
    ++size_;
  }

  T Pop() {
    if (!last_) {
      throw std::length_error("last_");
    }
    --size_;

    auto cur = last_;
    T cur_val = cur->value;
    last_ = cur->next;
    delete cur;
    return cur_val;
  }

  T Back() {
    return last_->value;
  }

  int Size() {
    return size_;
  }

  void Clear() {
    size_ = 0;
    while (last_) {
      auto cur = last_;
      last_ = cur->next;
      delete cur;
    }
  }
};

int main() {
  Stack<int> stack;

  int n;
  std::cin >> n;
  while (n--) {
    std::string request;
    std::cin >> request;

    if (request == "push") {
      int value;
      std::cin >> value;
      stack.Push(value);
      std::cout << "ok" << '\n';
    } else if (request == "pop") {
      std::cout << stack.Pop() << '\n';
    } else if (request == "back") {
      std::cout << stack.Back() << '\n';
    } else if (request == "size") {
      std::cout << stack.Size() << '\n';
    } else if (request == "clear") {
      stack.Clear();
      std::cout << "ok" << '\n';
    } else if (request == "exit") {
      std::cout << "bye" << '\n';
      stack.Clear();
      return 0;
    }
  }

  stack.Clear();
  return 0;
}