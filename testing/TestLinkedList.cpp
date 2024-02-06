//
// Created by Rohith on 1/13/24.
//
#include "gtest/gtest.h"
#include "LinkedList.h"
#include <vector>


TEST(LinkedList, TestInit){
    LinkedList list = {1,2,3,4,5};
    ASSERT_FALSE(list.is_empty());
    ASSERT_EQ(list.get_head_val(), 1);
    ASSERT_EQ(list.get_tail_val(), 5);
}

TEST(LinkedList, TestHeadTail){
    LinkedList list = {"first","second","Third","fourth","fifth"};
    std::string head = list.get_head_val();
    std::string tail = list.get_tail_val();
    ASSERT_EQ(head,"first");
    ASSERT_EQ(tail,"fifth");
}

TEST(LinkedList, TestCleanUp){
    LinkedList<int>* test;
    {
        LinkedList list = {1,2,3,4,5};
        test = &list;
        ASSERT_FALSE(list.is_empty());
        ASSERT_EQ(list.get_head_val(), 1);
        ASSERT_EQ(list.get_tail_val(), 5);
    }
    ASSERT_EQ(test->head, nullptr);
    ASSERT_EQ(test->tail, nullptr);
    ASSERT_EQ(test->size(), 0);
}

TEST(LinkedList, TestPosition){
    LinkedList list = {1,2,3,4,5};
    ASSERT_EQ(list.at(3)->data,4);
    ASSERT_EQ(list[1]->data, 2);
}

TEST(LinkedList, TestPositionOutOfBound){
    LinkedList list = {1,2,3,4,5};
    EXPECT_THROW(list.at(5),std::out_of_range);
}

TEST(LinkedList, TestDeleteAtPosition){
    LinkedList list = {1,2,3,4,5};
    auto ptr= list.at(2);
    ASSERT_EQ(ptr->data,3);
    list.delete_at(2);
    ASSERT_NE(ptr->data, 3);
    //todo: write SIGSEGV test case
}

TEST(LinkedList, TestBasicSorting){
    int data[] =  {4,5,6,7,8,9};
    LinkedList list = {9,8,7,6,5,4};
    list.sort();
    ASSERT_EQ(list.get_head_val(), 4);
    ASSERT_EQ(list.get_tail_val(), 9);
    for(int i=0; i<6; i++){
        ASSERT_EQ(list[i]->data, data[i]);
    }
}