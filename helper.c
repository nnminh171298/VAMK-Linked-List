#include "helper.h"
#include "linked_list.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

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

linked_list *generateNodeWithData(int index, char const *data)
{
	auto length = strlen(data);
	char *data_ptr = (char *) malloc(sizeof(char) * (length+1));
	strcpy(data_ptr, data);
	
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
	bool data_compare = false;
	if(node->data == nullptr && data == nullptr)
		data_compare = true;
	else if(node->data != nullptr && data != nullptr)
		data_compare = (strcmp(data, node->data) == 0);
	
	return (node->index == index) && (node->next == next) && data_compare;
}

void linkNodes(linked_list **prev_node, linked_list **next_node)
{
	(*prev_node)->next = *next_node;
}