#include <iostream>
#include <stack>
#include <string>
#include <string_view>

enum class Brackets { Parentheses, Square, Curly, Angle };

bool CheckBrackets(std::string_view str) {
  std::stack<Brackets> stck{};

  for (char ch : str) {
    switch (ch) {
      case '(':
        stck.push(Brackets::Parentheses);
        break;
      case '[':
        stck.push(Brackets::Square);
        break;
      case '{':
        stck.push(Brackets::Curly);
        break;
      case '<':
        stck.push(Brackets::Angle);
        break;

      case ')':
        if (stck.empty() || stck.top() != Brackets::Parentheses) {
          return false;
        }
        stck.pop();
        break;
      case ']':
        if (stck.empty() || stck.top() != Brackets::Square) {
          return false;
        }
        stck.pop();
        break;
      case '}':
        if (stck.empty() || stck.top() != Brackets::Curly) {
          return false;
        }
        stck.pop();
        break;
      case '>':
        if (stck.empty() || stck.top() != Brackets::Angle) {
          return false;
        }
        stck.pop();
        break;
    }
  }

  return stck.empty();
}

int main() {
  std::string str;
  std::cin >> str;

  std::cout << CheckBrackets(str);

  return 0;
}