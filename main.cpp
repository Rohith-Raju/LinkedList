//
// Created by Rohith on 1/10/24.
//
#include "LinkedList.h"
#include "iostream"

int main() {
  LinkedList<int> LList = {1, 2, 3, 4, 5};

  for (auto item : LList) {
    std::cout << item;
  }

  return 0;
}
