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
	auto head = list;
	int last_index = list->index;
	while(list->next != nullptr)
	{
		list = list->next;
		if(list == head)
			return -1;
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
	
	auto head = list;
	int count = 1;
	printf("Display list: ");
	print_data(list->data);
	
	while(true)
	{
		list = list->next;
		if(list != nullptr)
		{
			if(list == head)
			{
				printf("\n");
				return -1;
			}
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
	auto head = list;
	
	if(string == nullptr)
	{
		while(list != nullptr)
		{
			if(list->data == nullptr)
				return list;
			list = list->next;
			if(list == head)
				break;
		}
		return nullptr;
	}
	
	while(list != nullptr)
	{
		if(list->data != nullptr)
			if(strcmp(string, list->data) == 0)
				return list;
		list = list->next;
		if(list == head)
			break;
	}
	return nullptr;
}

int delete_from_list(linked_list *list, int index)
{
	if(list == nullptr)
		return -1;
	
	auto head = list;
	linked_list *prev = nullptr;
	while(true)
	{
		if(list == nullptr)
			return -1;
		if(list->index == index)
		{
			if(prev != nullptr)
				prev->next = list->next;
			else
				head = list->next; // delete first, get new head
			free(list->data); // nullptr still OK
			free(list);
			break;
		}
		prev = list;
		list = list->next;
		if(list == head)
			return -1;
	}
	
	// more specification needed
	// should the index start from 0?
	// or just decrement everything after the deleted node?
	int new_index = 0;
	list = head;
	while(list != nullptr)
	{
		list->index = new_index++;
		list = list->next;
	}
	
	return new_index;
}
