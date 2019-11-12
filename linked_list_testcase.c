#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include "linked_list.h"

//----------------------Helpers------------------------------------------------

linked_list *generateNode(int index, int data)
{
	char *data_ptr = (char *) malloc(sizeof(char) * 20);
	sprintf(data_ptr, "Data %d", data);
	
	linked_list *new_node = (linked_list *) malloc(sizeof(linked_list));
	new_node->data = data_ptr;
	new_node->index = index;
	new_node->next = nullptr;
	
	return new_node;
}

void freeNode(linked_list *node)
{
	free(node->data);
	free(node);
}

bool checkNode(linked_list *node, int index, char const *data, linked_list *next)
{
	int string_compare = strcmp(data, node->data);
	return (node->index == index) && (node->next == next) && (string_compare == 0);
}

void linkNodes(linked_list **prev_node, linked_list **next_node)
{
	(*prev_node)->next = *next_node;
}

//----------------------Add----------------------------------------------------

TEST(ADD, add_1_empty)
{
	linked_list *node_0 = nullptr;
	char *data = const_cast<char *>("Data 0");
	int result = add_to_list(node_0, data);
	
	EXPECT_EQ(-1, result);
}

TEST(ADD, add_2_head_given)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linkNodes(&node_0, &node_1);
	char *data = const_cast<char *>("Data 2");
	int result = add_to_list(node_0, data);
	
	EXPECT_EQ(2, result);
	EXPECT_NE(nullptr, node_1->next);
	if(node_1->next == nullptr)
	{
		freeNode(node_0);
		freeNode(node_1);
		return;
	}
	
	linked_list *node_2 = node_1->next;
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", nullptr));
	EXPECT_NE(data, node_2->data);
	
	freeNode(node_0);
	freeNode(node_1);
}

TEST(ADD, add_3_tail_given)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linkNodes(&node_0, &node_1);
	char *data = const_cast<char *>("Data 2");
	int result = add_to_list(node_1, data);
	
	EXPECT_EQ(2, result);
	EXPECT_NE(nullptr, node_1->next);
	if(node_1->next == nullptr)
	{
		freeNode(node_0);
		freeNode(node_1);
		return;
	}
	
	linked_list *node_2 = node_1->next;
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", nullptr));
	EXPECT_NE(data, node_2->data);
	
	freeNode(node_0);
	freeNode(node_1);
}

TEST(ADD, add_4_empty_string)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linkNodes(&node_0, &node_1);
	char *data = const_cast<char *>("");
	int result = add_to_list(node_1, data);
	
	EXPECT_EQ(2, result);
	EXPECT_NE(nullptr, node_1->next);
	if(node_1->next == nullptr)
	{
		freeNode(node_0);
		freeNode(node_1);
		return;
	}
	
	linked_list *node_2 = node_1->next;
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "", nullptr));
	EXPECT_NE(data, node_2->data);
	
	freeNode(node_0);
	freeNode(node_1);
}

TEST(ADD, add_5_NULL_string)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linkNodes(&node_0, &node_1);
	int result = add_to_list(node_1, nullptr);
	
	EXPECT_EQ(-1, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
}

TEST(ADD, add_6_out_of_index)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_max = generateNode(0x7FFF'FFFF, 0x7FFF'FFFF);
	linkNodes(&node_0, &node_max);
	char *data = const_cast<char *>("Data max+1");
	int result = add_to_list(node_max, data);
	
	EXPECT_EQ(-1, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_max));
	EXPECT_TRUE(checkNode(node_max, 0x7FFF'FFFF, "Data 2147483647", nullptr));
	
	freeNode(node_0);
	freeNode(node_max);
}

//----------------------Display-item-------------------------------------------

TEST(DISP_ITEM, disp_item_1_empty)
{
	linked_list *node_0 = nullptr;
	int result = display_item(node_0);
	
	EXPECT_EQ(-1, result);
}

TEST(DISP_ITEM, disp_item_2_head)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	int result = display_item(node_0);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(DISP_ITEM, disp_item_3_mid)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	int result = display_item(node_1);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(DISP_ITEM, disp_item_4_tail)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	int result = display_item(node_2);
	
	EXPECT_EQ(0, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(DISP_ITEM, disp_item_5_NULL_string)
{
	linked_list *node_0 = (linked_list *) malloc(sizeof(linked_list));
	node_0->data = nullptr;
	node_0->index = 0;
	node_0->next = nullptr;
	int result = display_item(node_0);
	
	EXPECT_EQ(0, result);
	EXPECT_EQ(0, node_0->index);
	
	free(node_0);
}

//----------------------Display-list-------------------------------------------

TEST(DISP_LIST, disp_list_1_empty)
{
	linked_list *node_0 = nullptr;
	int result = display_list(node_0);
	
	EXPECT_EQ(-1, result);
}

TEST(DISP_LIST, disp_list_2_normal_one)
{
	linked_list *node_0 = generateNode(0, 0);
	int result = display_list(node_0);
	
	EXPECT_EQ(1, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", nullptr));
	
	freeNode(node_0);
}

TEST(DISP_LIST, disp_list_3_normal_many)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	int result = display_list(node_0);
	
	EXPECT_EQ(3, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(DISP_LIST, disp_list_4_NULL_string_head)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	
	auto save_str = node_0->data;
	node_0->data = nullptr;
	int result = display_list(node_0);
	node_0->data = save_str;
	
	EXPECT_EQ(3, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(DISP_LIST, disp_list_5_NULL_string_mid)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	
	auto save_str = node_1->data;
	node_1->data = nullptr;
	int result = display_list(node_0);
	node_1->data = save_str;
	
	EXPECT_EQ(3, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

//----------------------Search-from-list---------------------------------------

TEST(SEARCH, search_1_empty)
{
	linked_list *node_0 = nullptr;
	auto result = search_from_list(node_0, const_cast<char *>("Data 0"));
	
	EXPECT_EQ(nullptr, result);
}

TEST(SEARCH, search_2_normal)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	auto result = search_from_list(node_0, const_cast<char *>("Data 1"));
	
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(result, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(SEARCH, search_3_empty_string)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	
	auto save_str = node_2->data;
	char *empty_string = const_cast<char *>("");
	node_2->data = empty_string;
	auto result = search_from_list(node_0, const_cast<char *>(""));
	
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "", nullptr));
	EXPECT_TRUE(checkNode(result, 2, "", nullptr));
	
	node_2->data = save_str;
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(SEARCH, search_4_NULL_string)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	
	auto save_str = node_2->data;
	node_2->data = nullptr;
	auto result = search_from_list(node_0, nullptr);
	node_2->data = save_str;
	
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", nullptr));
	EXPECT_TRUE(checkNode(result, 2, "Data 2", nullptr));
	
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(SEARCH, search_5_not_found)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	auto result = search_from_list(node_0, const_cast<char *>("Something strange"));
	
	EXPECT_EQ(nullptr, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

//----------------------Delete-from-list---------------------------------------

TEST(DELETE, delete_1_empty)
{
	linked_list *node_0 = nullptr;
	int result = delete_from_list(node_0, 0);
	
	EXPECT_EQ(-1, result);
}

TEST(DELETE, delete_2_normal)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	auto result = delete_from_list(node_0, 1);
	
	EXPECT_EQ(2, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_2));
	EXPECT_TRUE(checkNode(node_2, 1, "Data 2", nullptr));
	
	freeNode(node_0);
	freeNode(node_2);
}

TEST(DELETE, delete_3_not_found)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	auto result = delete_from_list(node_0, 4);
	
	EXPECT_EQ(-1, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 2, "Data 2", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
	freeNode(node_2);
}

TEST(DELETE, delete_4_head)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	auto result = delete_from_list(node_0, 0);
	
	EXPECT_EQ(2, result);
	EXPECT_TRUE(checkNode(node_1, 0, "Data 1", node_2));
	EXPECT_TRUE(checkNode(node_2, 1, "Data 2", nullptr));
	
	freeNode(node_1);
	freeNode(node_2);
}

TEST(DELETE, delete_5_tail)
{
	linked_list *node_0 = generateNode(0, 0);
	linked_list *node_1 = generateNode(1, 1);
	linked_list *node_2 = generateNode(2, 2);
	linkNodes(&node_0, &node_1);
	linkNodes(&node_1, &node_2);
	auto result = delete_from_list(node_0, 2);
	
	EXPECT_EQ(2, result);
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", nullptr));
	
	freeNode(node_0);
	freeNode(node_1);
}

TEST(DELETE, delete_6_only)
{
	linked_list *node_0 = generateNode(0, 0);
	auto result = delete_from_list(node_0, 0);
	
	EXPECT_EQ(0, result);
}