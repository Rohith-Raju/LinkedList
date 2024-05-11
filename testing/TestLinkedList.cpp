//
// Created by Rohith on 1/13/24.
//
#include "LinkedList.h"
#include "gtest/gtest.h"

TEST(LinkedList, TestPrimitiveInit) {
  LinkedList list = {1, 2, 3, 4, 5};
  ASSERT_FALSE(list.is_empty());
  ASSERT_EQ(list.get_head_val(), 1);
  ASSERT_EQ(list.get_tail_val(), 5);
}

TEST(LinkedList, TestNonPrimitiveInit) {
  class Person {
  public:
    int age;
    std::string name;
  };
  LinkedList<Person> list = {
      {23, "Rohith"}, {25, "John"}, {21, "Bob"}, {28, "Alice"}, {30, "Rahul"}};
  int ageArr[5] = {23, 25, 21, 28, 30};
  std::string nameArr[5] = {"Rohith", "John", "Bob", "Alice", "Rahul"};
  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(list[i]->data.age, ageArr[i]);
    ASSERT_EQ(list[i]->data.name, nameArr[i]);
  }
}

TEST(LinkedList, TestCopyConstructor) {
  LinkedList<int> list1 = {1, 2, 3, 4, 5};
  LinkedList<int> list2(list1);
  bool result = list1 == list2 ? true : false;
  ASSERT_TRUE(result);
}

TEST(LinkedList, TestHeadTail) {
  LinkedList list = {"first", "second", "Third", "fourth", "fifth"};
  std::string head = list.get_head_val();
  std::string tail = list.get_tail_val();
  ASSERT_EQ(head, "first");
  ASSERT_EQ(tail, "fifth");
}

TEST(LinkedList, TestMoveConstructor) {
  LinkedList<int> list = {1, 2, 3, 4, 5};
  LinkedList<int> list2((LinkedList<int> &&)list);
  ASSERT_EQ(list2.get_head_val(), 1);
  ASSERT_EQ(list2.get_tail_val(), 5);
  ASSERT_EQ(list.head, nullptr);
  ASSERT_EQ(list.tail, nullptr);
}

TEST(LinkedList, TestCleanUp) {
  LinkedList<int> *test;
  {
    LinkedList list = {1, 2, 3, 4, 5};
    test = &list;
    ASSERT_FALSE(list.is_empty());
    ASSERT_EQ(list.get_head_val(), 1);
    ASSERT_EQ(list.get_tail_val(), 5);
  }
  ASSERT_EQ(test->head, nullptr);
  ASSERT_EQ(test->tail, nullptr);
  ASSERT_EQ(test->size(), 0);
}

TEST(LinkedList, TestPosition) {
  LinkedList list = {1, 2, 3, 4, 5};
  ASSERT_EQ(list.at(3)->data, 4);
  ASSERT_EQ(list[1]->data, 2);
}

TEST(LinkedList, TestPositionOutOfBound) {
  LinkedList list = {1, 2, 3, 4, 5};
  EXPECT_THROW(list.at(5), std::out_of_range);
}

TEST(LinkedList, TestDeleteAtPosition) {
  LinkedList list = {1, 2, 3, 4, 5};
  auto ptr = list.at(2);
  ASSERT_EQ(ptr->data, 3);
  list.delete_at(2);
  ASSERT_NE(ptr->data, 3);
}

TEST(LinkedList, TestDeleteAtEnd) {
  LinkedList list = {1, 2, 3, 4, 5};
  ASSERT_EQ(list.get_tail_val(), 5);
  list.delete_at(4);
  ASSERT_EQ(list.get_tail_val(), 4);
}

TEST(LinkedList, TestCustomSort) {
  class Person {
  public:
    int age;
    std::string name;
  };
  LinkedList<Person> list = {
      {23, "Rohith"}, {22, "John"}, {21, "Bob"}, {20, "Alice"}, {19, "Rahul"}};
  list.sort([](Person left, Person right) { return left.age < right.age; });
  int data[5] = {19, 20, 21, 22, 23};
  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(data[i], list[i]->data.age);
  }
}

TEST(LinkedList, TestIterator) {
  LinkedList myList = {1, 2, 3, 4, 6};
  int checkArr[] = {1, 2, 3, 4, 6};
  int index = 0;
  for (auto i : myList) {
    ASSERT_EQ(checkArr[index], i);
    index++;
  }
}

TEST(LinkedList, TestReverseIterator) {
  LinkedList myList = {1, 2, 3, 4, 5};
  int checkArr[] = {5, 4, 3, 2, 1};
  int index = 0;
  for (auto it = myList.rbegin(); it != myList.rend(); it++) {
    ASSERT_EQ(checkArr[index], *it);
    index++;
  }
}

TEST(LinkedList, TestReverse) {
  LinkedList myList = {1, 2, 3, 4, 5, 6};
  int checkArr[] = {6, 5, 4, 3, 2, 1};
  myList.reverse();
  ASSERT_EQ(myList.head->data, 6);
  ASSERT_EQ(myList.tail->data, 1);
  int index = 0;
  for (auto i : myList) {
    ASSERT_EQ(checkArr[index], i);
    index++;
  }
}

TEST(LinkedList, TestEquals) {
  LinkedList my_list_1 = {1, 2, 3, 4, 5};
  LinkedList my_list_2 = {1, 2, 3, 4, 5};
  LinkedList my_list_3 = {1, 2, 2, 3, 4};
  bool result = my_list_1 == my_list_2 ? true : false;
  bool result2 = my_list_1 == my_list_3 ? true : false;
  ASSERT_TRUE(result);
  ASSERT_FALSE(result2);
}
