//
// Created by Rohith on 1/10/24.
//
#include "LinkedList.h"
#include "iostream"

int main() {
  {
    LinkedList myList = {3, 2};
    myList.sort();
    for (auto it : myList) {
      std::cout << it;
    }
  }
}
