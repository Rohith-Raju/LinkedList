//
// Created by Rohith on 1/13/24.
//
#include "gtest/gtest.h"
#include "LinkedList.h"


TEST(LinkedList, Test_Init){
    LinkedList list = {1,2,3,4,5};
    ASSERT_FALSE(list.is_empty());
}

TEST(LinkedList, TEST_Head_Tail){
    LinkedList list = {"first","second","Third","fourth","fifth"};
    std::string head = list.get_head();
    std::string tail = list.get_tail();
    ASSERT_EQ(head,"first");
    ASSERT_EQ(tail,"fifth");
}

TEST(LinkedList, Test_Position){
    LinkedList list = {1,2,3,4,5};
    ASSERT_EQ(list.at(3),4);
    ASSERT_EQ(list[1], 2);
}

TEST(LinkedList, Test_Position_Out_of_bound){
    LinkedList list = {1,2,3,4,5};
    EXPECT_THROW(list.at(5),std::out_of_range);
}
