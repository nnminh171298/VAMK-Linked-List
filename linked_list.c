#include "linked_list.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

int add_to_list(linked_list *list, char *string)
{
	// cannot replace NULL list with new node
	// need (linked_list **list)
	if(list == NULL || string == NULL)
		return -1;
	
	// find tail
	int last_index = list->index;
	while(list->next != NULL)
	{
		list = list->next;
		last_index = list->index;
	}
	
	// create new data
	auto length = strlen(string);
	char *data_ptr = (char *) malloc(sizeof(char) * (length+1));
	if(data_ptr == nullptr)
		return -1;
	strcpy(data_ptr, string);
	
	// create new node
	linked_list *new_node = (linked_list *) malloc(sizeof(linked_list));
	if(new_node == nullptr)
		return -1;
	new_node->data = data_ptr;
	new_node->index = last_index + 1;
	new_node->next = nullptr;
	
	// add to list
	list->next = new_node;
	return new_node->index;
}

int display_item(linked_list *list)
{
	
}

int display_list(linked_list *list)
{
	
}

linked_list *search_from_list(linked_list *list, char *string)
{
	
}

int delete_from_list(linked_list *list, int index)
{
	
}

int empty_list(linked_list *list)
{
	
}

int swap_items(linked_list *node_1, linked_list *node_2)
{
	
}

int sort_list(linked_list *list)
{
	
}

int linkedlist_status(linked_list *list)
{
	
}
