#include <gtest/gtest.h>

#include "helper.h"
#include "linked_list.h"

//----------------------Empty--------------------------------------------------

TEST(EMPTY, empty_1_NULL)
{
	linked_list *node_0 = nullptr;
	int result = empty_list(node_0);
	
	EXPECT_EQ(-1, result);
}

TEST(EMPTY, empty_2_one)
{
	linked_list *node_0 = generateNode(0, 0);
	int result = empty_list(node_0);
	
	EXPECT_EQ(1, result);
}

TEST(EMPTY, empty_3_many)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	int result = empty_list(node_0);
	
	EXPECT_EQ(3, result);
}

//----------------------Swap-items---------------------------------------------

TEST(SWAP, swap_1_NULL_first)
{
	linked_list *node_0 = generateNode(0, 0);
	int result = swap_items(nullptr, node_0);
	
	EXPECT_EQ(-1, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", nullptr));
	
	freeNode(node_0);
}

TEST(SWAP, swap_2_NULL_second)
{
	linked_list *node_0 = generateNode(0, 0);
	int result = swap_items(node_0, nullptr);
	
	EXPECT_EQ(-1, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", nullptr));
	
	freeNode(node_0);
}

TEST(SWAP, swap_3_NULL_both)
{
	int result = swap_items(nullptr, nullptr);
	EXPECT_EQ(-1, result);
}

TEST(SWAP, swap_4_same_data)
{
	linked_list *node_0 = generateNode(0, 0);
	int result = swap_items(node_0, node_0);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", nullptr));
	
	freeNode(node_0);
}

TEST(SWAP, swap_5_normal)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linked_list *node_3 = generateNode(3, 3);
	linked_list *node_4 = generateNode(4, 4);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	linkNodes(&node_2, &node_3);
	linkNodes(&node_3, &node_4);
	int result = swap_items(node_1, node_3);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 3", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", node_3));
	EXPECT_TRUE(checkNode(node_3, 3, "Data 1", node_4));
	EXPECT_TRUE(checkNode(node_4, 4, "Data 4", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
	freeNode(node_3);
	freeNode(node_4);
}

TEST(SWAP, swap_6_adjacent)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linked_list *node_3 = generateNode(3, 3);
	linked_list *node_4 = generateNode(4, 4);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	linkNodes(&node_2, &node_3);
	linkNodes(&node_3, &node_4);
	int result = swap_items(node_1, node_2);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 2", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 1", node_3));
	EXPECT_TRUE(checkNode(node_3, 3, "Data 3", node_4));
	EXPECT_TRUE(checkNode(node_4, 4, "Data 4", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
	freeNode(node_3);
	freeNode(node_4);
}

TEST(SWAP, swap_7_head)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linked_list *node_3 = generateNode(3, 3);
	linked_list *node_4 = generateNode(4, 4);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	linkNodes(&node_2, &node_3);
	linkNodes(&node_3, &node_4);
	int result = swap_items(node_0, node_2);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 2", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 0", node_3));
	EXPECT_TRUE(checkNode(node_3, 3, "Data 3", node_4));
	EXPECT_TRUE(checkNode(node_4, 4, "Data 4", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
	freeNode(node_3);
	freeNode(node_4);
}

TEST(SWAP, swap_8_tail)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linked_list *node_3 = generateNode(3, 3);
	linked_list *node_4 = generateNode(4, 4);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	linkNodes(&node_2, &node_3);
	linkNodes(&node_3, &node_4);
	int result = swap_items(node_4, node_2);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 4", node_3));
	EXPECT_TRUE(checkNode(node_3, 3, "Data 3", node_4));
	EXPECT_TRUE(checkNode(node_4, 4, "Data 2", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
	freeNode(node_3);
	freeNode(node_4);
}

//----------------------Sort-list----------------------------------------------

TEST(SORT, sort_1_NULL)
{
	int result = sort_list(nullptr);
	EXPECT_EQ(-1, result);
}

TEST(SORT, sort_2_one)
{
	linked_list *node_0 = generateNode(0, 0);
	int result = sort_list(node_0);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", nullptr));
	
	freeNode(node_0);
}

TEST(SORT, sort_3_normal)
{
	linked_list *node_0 = generateNode(0, 1); // index 0, data 1
	linked_list *node_1 = generateNode(1, 2); // index 1, data 2
	linked_list *node_2 = generateNode(2, 0); // index 2, data 0
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	int result = sort_list(node_0);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_2, 0, "Data 0", node_0));
	EXPECT_TRUE(checkNode(node_0, 1, "Data 1", node_1));
	EXPECT_TRUE(checkNode(node_1, 2, "Data 2", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(SORT, sort_4_different_data)
{
	linked_list *node_0 = generateNodeWithData(0, "My-name-is-Doof");
	linked_list *node_1 = generateNodeWithData(1, "And-you-do-what-I-said");
	linked_list *node_2 = generateNodeWithData(2, "Whoop-whoop");
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	int result = sort_list(node_0);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_1, 0, "And-you-do-what-I-said", node_0));
	EXPECT_TRUE(checkNode(node_0, 1, "My-name-is-Doof", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Whoop-whoop", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(SORT, sort_5_same_data_different_length)
{
	linked_list *node_0 = generateNodeWithData(0, "Noone-loves-yo");
	linked_list *node_1 = generateNodeWithData(1, "Noone-loves-yogurt");
	linked_list *node_2 = generateNodeWithData(2, "Noone-loves");
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	int result = sort_list(node_0);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_2, 0, "Noone-loves", node_0));
	EXPECT_TRUE(checkNode(node_0, 1, "Noone-loves-yo", node_1));
	EXPECT_TRUE(checkNode(node_1, 2, "Noone-loves-yogurt", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(SORT, sort_6_same_data)
{
	linked_list *node_0 = generateNode(0, 4);
	linked_list *node_1 = generateNode(1, 3);
	linked_list *node_2 = generateNode(2, 2);
	linked_list *node_3 = generateNode(3, 2);
	linked_list *node_4 = generateNode(4, 0);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	linkNodes(&node_2, &node_3);
	linkNodes(&node_3, &node_4);
	int result = sort_list(node_0);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_4, 0, "Data 0", node_3) || checkNode(node_4, 0, "Data 0", node_2));
	EXPECT_TRUE(checkNode(node_3, 1, "Data 2", node_2) || checkNode(node_3, 2, "Data 2", node_1));
	EXPECT_TRUE(checkNode(node_2, 1, "Data 2", node_3) || checkNode(node_2, 2, "Data 2", node_1));
	EXPECT_TRUE(checkNode(node_1, 3, "Data 3", node_0));
	EXPECT_TRUE(checkNode(node_1, 4, "Data 4", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

//----------------------Status-------------------------------------------------

TEST(STATUS, status_1_NULL)
{
	int result = linkedlist_status(nullptr);
	EXPECT_EQ(-1, result);
}

TEST(STATUS, status_2_one)
{
	linked_list *node_0 = generateNode(0, 0);
	int result = linkedlist_status(node_0);
	
	EXPECT_EQ(1, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", nullptr));
	
	freeNode(node_0);
}

TEST(STATUS, status_3_many)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	int result = linkedlist_status(node_0);
	
	EXPECT_EQ(3, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}