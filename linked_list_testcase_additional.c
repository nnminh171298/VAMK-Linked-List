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

TEST(EMPTY, empty_4_loop)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linked_list *node_3 = generateNode(3, 3);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	linkNodes(&node_2, &node_3);
	linkNodes(&node_3, &node_1);
	auto result = empty_list(node_0);
	
	EXPECT_EQ(-1, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", node_3));
	EXPECT_TRUE(checkNode(node_3, 3, "Data 3", node_1));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
	freeNode(node_3);
}

TEST(EMPTY, empty_5_overlap_string)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	
	auto saved_string = node_1->data;
	node_1->data = (node_0->data + 1);
	
	auto result = empty_list(node_0);
	EXPECT_EQ(1, result);
	
	node_1->data = saved_string;
	freeNode(node_0);
	freeNode(node_1);
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
	EXPECT_TRUE(checkNode(node_1, 3, "Data 3", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", node_3));
	EXPECT_TRUE(checkNode(node_3, 1, "Data 1", node_4));
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
	EXPECT_TRUE(checkNode(node_1, 2, "Data 2", node_2));
	EXPECT_TRUE(checkNode(node_2, 1, "Data 1", node_3));
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
	EXPECT_TRUE(checkNode(node_0, 2, "Data 2", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 0, "Data 0", node_3));
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
	EXPECT_TRUE(checkNode(node_2, 4, "Data 4", node_3));
	EXPECT_TRUE(checkNode(node_3, 3, "Data 3", node_4));
	EXPECT_TRUE(checkNode(node_4, 2, "Data 2", nullptr));
	
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
	linked_list *node_0 = generateNode(1, 1);
	linked_list *node_1 = generateNode(2, 2);
	linked_list *node_2 = generateNode(0, 0);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	int result = sort_list(node_0);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(SORT, sort_4_different_data)
{
	linked_list *node_0 = generateNodeWithData(1, "My-name-is-Doof");
	linked_list *node_1 = generateNodeWithData(0, "And-you-do-what-I-said");
	linked_list *node_2 = generateNodeWithData(2, "Whoop-whoop");
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	int result = sort_list(node_0);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_0, 0, "And-you-do-what-I-said", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "My-name-is-Doof", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Whoop-whoop", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(SORT, sort_5_same_data_different_length)
{
	linked_list *node_0 = generateNodeWithData(1, "Noone-loves-yo");
	linked_list *node_1 = generateNodeWithData(2, "Noone-loves-yogurt");
	linked_list *node_2 = generateNodeWithData(0, "Noone-loves");
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	int result = sort_list(node_0);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Noone-loves", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Noone-loves-yo", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Noone-loves-yogurt", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(SORT, sort_6_same_data)
{
	linked_list *node_0 = generateNode(4, 4);
	linked_list *node_1 = generateNode(3, 3);
	linked_list *node_2 = generateNode(2, 2); // same "Data 2" here
	linked_list *node_3 = generateNode(2, 2); // same "Data 2" here
	linked_list *node_4 = generateNode(0, 0);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	linkNodes(&node_2, &node_3);
	linkNodes(&node_3, &node_4);
	int result = sort_list(node_0);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 2, "Data 2", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", node_3));
	EXPECT_TRUE(checkNode(node_3, 3, "Data 3", node_4));
	EXPECT_TRUE(checkNode(node_4, 4, "Data 4", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
	freeNode(node_3);
	freeNode(node_4);
}

TEST(SORT, sort_7_loop)
{
	linked_list *node_0 = generateNode(3, 3);
	linked_list *node_1 = generateNode(2, 2);
	linked_list *node_2 = generateNode(1, 1);
	linked_list *node_3 = generateNode(0, 0);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	linkNodes(&node_2, &node_3);
	linkNodes(&node_3, &node_1);
	auto result = sort_list(node_0);
	
	EXPECT_EQ(-1, result);
	EXPECT_TRUE(checkNode(node_0, 3, "Data 3", node_1));
	EXPECT_TRUE(checkNode(node_1, 2, "Data 2", node_2));
	EXPECT_TRUE(checkNode(node_2, 1, "Data 1", node_3));
	EXPECT_TRUE(checkNode(node_3, 0, "Data 0", node_1));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
	freeNode(node_3);
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

TEST(STATUS, status_4_loop)
{
	linked_list *node_0 = generateNode(0, 3);
	linked_list *node_1 = generateNode(1, 2);
	linked_list *node_2 = generateNode(2, 1);
	linked_list *node_3 = generateNode(3, 0);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	linkNodes(&node_2, &node_3);
	linkNodes(&node_3, &node_1);
	auto result = linkedlist_status(node_0);
	
	EXPECT_EQ(-1, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 3", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 2", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 1", node_3));
	EXPECT_TRUE(checkNode(node_3, 3, "Data 0", node_1));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
	freeNode(node_3);
}