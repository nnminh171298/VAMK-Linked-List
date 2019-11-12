#include "linked_list.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

//----------------------Helpers------------------------------------------------

void print_data(char *data)
{
	if(data != nullptr)
		printf("%s", data);
	else
		printf("<null>");
}

//----------------------Functions----------------------------------------------

int add_to_list(linked_list *list, char *string)
{
	// cannot replace NULL list with new node
	// need (linked_list **list)
	if(list == nullptr || string == nullptr)
		return -1;
	
	// find tail
	int last_index = list->index;
	while(list->next != nullptr)
	{
		list = list->next;
		last_index = list->index;
	}
	if(last_index == 0x7FFF'FFFF)
		return -1;
	
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
	if(list == nullptr)
		return -1;
	
	printf("Display item: ");
	print_data(list->data);
	printf("\n");
	
	return 0;
}

int display_list(linked_list *list)
{
	if(list == nullptr)
		return -1;
	
	int count = 1;
	printf("Display list: ");
	print_data(list->data);
	
	while(true)
	{
		list = list->next;
		if(list != nullptr)
		{
			printf(" - ");
			print_data(list->data);
			count++;
		}
		else
			break;
	}
	printf("\n");
	return count;
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
