#include <iostream>
#include <memory>
#include <sstream>
#include <string>

int main() {
  struct Node {
    int data{};
    Node* next{};
  };

  std::string input{};
  std::getline(std::cin >> std::ws, input);
  std::istringstream iss{input};

  int num{};
  iss >> num;
  Node* list_head = new Node{num, nullptr};
  Node* tail = list_head;
  while (iss >> num) {
    Node* tmp = new Node{num, nullptr};
    tail->next = tmp;
    tail = tmp;
  }

  int k{};
  std::cin >> k;

  Node* current = list_head;
  Node* next = nullptr;
  Node* prev = nullptr;
  while (current) {
    next = current->next;
    if (current->data != k) {
      current->next = prev;
      prev = current;
    } else {
      delete current;
    }
    current = next;
  }
  list_head = prev;

  current = list_head;
  while (current) {
    std::cout << current->data << ' ';
    next = current->next;
    delete current;
    current = next;
  }

  return 0;
}