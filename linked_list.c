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

// assume not null
bool isCircular(linked_list *list)
{
	linked_list *nodes[1000];
	int count = 0;
	while(true)
	{
		for(int i=0; i<count; i++)
			if(nodes[i] == list)
				return true;
		if(list->next == nullptr)
			return false;
		nodes[count] = list;
		list = list->next;
		count++;
	}
}

// assume not circular and not null
bool isStringOverlap(linked_list *head, linked_list *node)
{
	char *strings[1000];
	int lengths[1000];
	int count = 0;
	while(true)
	{
		if(head->data == nullptr)
			continue;
		
		// compare ending 
		for(int i=0; i<count; i++)
			if(node->data + strlen(node->data) == strings[i] + lengths[i])
				return true;
		
		if(head->next == nullptr)
			return false;
		
		if(node != head)
		{
			strings[count] = head->data;
			lengths[count] = strlen(head->data);
			count++;
		}
		head = head->next;
	}
}

//----------------------Functions----------------------------------------------

int add_to_list(linked_list *list, char *string)
{
	// cannot replace NULL list with new node
	// need (linked_list **list)
	if(list == nullptr || string == nullptr || isCircular(list))
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
	if(list == nullptr || isCircular(list))
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
	if(list == nullptr || isCircular(list))
		return nullptr;
	
	if(string == nullptr)
	{
		while(list != nullptr)
		{
			if(list->data == nullptr)
				return list;
			list = list->next;
		}
		return nullptr;
	}
	
	while(list != nullptr)
	{
		if(list->data != nullptr)
			if(strcmp(string, list->data) == 0)
				return list;
		list = list->next;
	}
	return nullptr;
}

int delete_from_list(linked_list *list, int index)
{
	if(list == nullptr || isCircular(list))
		return -1;
	
	auto head = list;
	linked_list *prev = nullptr;
	while(true)
	{
		if(list == nullptr)
			return -1;
		if(list->index == index)
		{
			if(isStringOverlap(head, list))
				return -1;
			if(prev != nullptr)
				prev->next = list->next; // update A-B-C to A-C
			else
				head = list->next; // delete first, get new head
			free(list->data); // nullptr still OK
			free(list);
			break;
		}
		prev = list;
		list = list->next;
	}
	
	if(head == nullptr)
		return 0;
	
	// get the first item to reorder
	if(prev == nullptr)
		list = head;
	else if(prev->next != nullptr)
		list = prev->next;
	else
		return prev->index + 1;
	
	while(true)
	{
		list->index--;
		if(list->next == nullptr)
			break;
		list = list->next;
	}
	
	return list->index + 1;
}
