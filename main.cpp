//
// Created by Rohith on 1/10/24.
//
#include "LinkedList.h"
#include "iostream"

int main() {
  LinkedList<int> list = {1, 2, 3, 4, 5};
  for (auto it = list.rbegin(); it != list.rend(); it++) {
    std::cout << *it;
  }
}
