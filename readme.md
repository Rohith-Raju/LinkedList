# LinkedList 
This project consits of templated version of linear linked list that mimics the style used in C++ standard template library. 
This project was done to learn, understand and practice concepts specifically tied to C++. 

## Prequisite
This project uses C++17 and cmake version 3.27. 

## Usage 
```c++
#include "LinkedList.h"
#include "iostream"

int main() {
  LinkedList<int> LList = {1, 2, 3, 4, 5};

  for (auto item : LList) {
    std::cout << item;
  }

  return 0;
}
```

## Testing 
`Gtest` is used as the testing framework. To build tests

```
mkdir build && cd build
cmake ../
cd testing
make 
```

To run the tests

```
./LinkedList_test
```


