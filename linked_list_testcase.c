#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include "linked_list.h"

//----------------------Helpers------------------------------------------------

linked_list *generateNode(int index, int data)
{
	char *data_ptr = (char *) malloc(sizeof(char) * 10);
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
	return (node->index == index) && (node->next == next) && string_compare;
}

//----------------------Add----------------------------------------------------

TEST(ADD, add_1_empty)
{
	linked_list *node_0 = nullptr;
	char *data = const_cast<char *>("Data 0");
	int result = add_to_list(node_0, data);
	
	EXPECT_EQ(0, result);
	EXPECT_NE(nullptr, node_0);
	if(node_0 == nullptr)
		return;
	
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", nullptr));
	EXPECT_NE(data, node_0->data);
}

TEST(ADD, add_2_normal)
{
	linked_list *node_0 = generateNode(0, 0);
	char *data = const_cast<char *>("Data 1");
	int result = add_to_list(node_0, data);
	
	EXPECT_EQ(1, result);
	EXPECT_NE(nullptr, node_0);
	if(node_0->next == nullptr)
	{
		freeNode(node_0);
		return;
	}
	
	linked_list *node_1 = node_0->next;
	EXPECT_TRUE(checkNode(node_0, 0, "Data 0", node_1));
	EXPECT_TRUE(checkNode(node_1, 1, "Data 1", nullptr));
	EXPECT_NE(data, node_1->data);
	
	freeNode(node_0);
}