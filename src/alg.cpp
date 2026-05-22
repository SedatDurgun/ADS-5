// Copyright 2025 NNTU-CS
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>
#include "tstack.h"

int prev(char c) {
  if (c == '*' || c == '/') return 2;
  if (c == '+' || c == '-') return 1;
  return 0;
}

bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string res;
  int i = 0;
  while (i < static_cast<int>(inf.size())) {
    char c = inf[i];
    if (c == ' ') {
      i++;
      continue;
    }
    if (isdigit(c)) {
      if (!res.empty()) res += ' ';
      while (i < static_cast<int>(inf.size()) && isdigit(inf[i])) {
        res += inf[i];
        i++;
      }
      continue;
    }
    if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        res += ' ';
        res += stack.pop();
      }
      if (!stack.isEmpty()) stack.pop();
    } else if (isOperator(c)) {
      while (!stack.isEmpty() &&
             isOperator(stack.get()) &&
             prev(stack.get()) >= prev(c)) {
        res += ' ';
        res += stack.pop();
      }
      stack.push(c);
    }
    i++;
  }
  while (!stack.isEmpty()) {
    res += ' ';
    res += stack.pop();
  }
  return res;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::istringstream iss(post);
  std::string token;
  while (iss >> token) {
    if (isdigit(token[0])) {
      stack.push(std::stoi(token));
    } else if (token.size() == 1 && isOperator(token[0])) {
      int b = stack.pop();
      int a = stack.pop();
      int res = 0;
      switch (token[0]) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/':
          if (b == 0) throw std::runtime_error("Sifira bolme");
          res = a / b;
          break;
      }
      stack.push(res);
    }
  }
  return stack.pop();
}
