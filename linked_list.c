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
	if(node->data == nullptr)
		return false;

	char *strings[1000];
	int lengths[1000];
	int count = 0;
	while(true)
	{
		if(head->data == nullptr)
		{
			head = head->next;
			continue;
		}
		
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

// return true if node_1 after node_2, false otherwise
bool isWrongOrder(linked_list *node_1, linked_list *node_2)
{
	if(node_1->data == nullptr)
		return false;
	if(node_2->data == nullptr)
		return true;
	
	return (strcmp(node_1->data, node_2->data) > 0);
}

//----------------------Basic--------------------------------------------------

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
	new_node->prev = list;
	
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
	
	linked_list *head = list;
	linked_list *after_deleted = nullptr;
	while(true)
	{
		if(list == nullptr)
			return -1;
		if(list->index == index)
		{
			if(isStringOverlap(head, list))
				return -1;

			linked_list *to_be_deleted = list;
			if(list->next != nullptr)
				list->next->prev = list->prev;
			if(list->prev != nullptr)
				list->prev->next = list->next;
			else
				head = list->next;
			after_deleted = list->next;

			free(to_be_deleted->data); // nullptr still OK
			free(to_be_deleted);
			break;
		}
		list = list->next;
	}
	
	list = head;
	int count{0};
	bool decrease_index{false};
	while(list != nullptr)
	{
		if(list == after_deleted)
			decrease_index = true;
		if(decrease_index)
			list->index--;
		count++;
		list = list->next;
	}
	
	return count;
}

//----------------------Additional---------------------------------------------

int empty_list(linked_list *list)
{
	if(list == nullptr || isCircular(list))
		return -1;
	
	auto head = list;
	int count = 0;
	linked_list *next = nullptr;
	while(true)
	{
		next = list->next;
		if(isStringOverlap(head, list))
			goto DELETE_NEXT;
		
		if(list == head)
			head = next;
		free(list->data);
		free(list);
		count++;
	
	DELETE_NEXT:
		if(next == nullptr)
			return count;
		list = next;
	}
}

int swap_items(linked_list *node_1, linked_list *node_2)
{
	if(node_1 == nullptr || node_2 == nullptr)
		return -1;
	
	linked_list temp;
	temp.data = node_1->data;
	node_1->data = node_2->data;
	node_2->data = temp.data;
	
	return 0;
}

int sort_list(linked_list *list)
{
	int count = linkedlist_status(list);
	if(count <= 0)
		return -1;
	
	auto head = list;
	
	// optimized bubble sort
	int unsorted_count = count;
	while(unsorted_count > 1)
	{
		int last_swap_pos = 0;
		for(int i=0; i<unsorted_count-1; i++)
		{
			if(isWrongOrder(list, list->next))
			{
				swap_items(list, list->next);
				last_swap_pos = i;
			}
			list = list->next;
		}
		unsorted_count = last_swap_pos + 1;
		list = head;
	}
	
	return 0;
}

int linkedlist_status(linked_list *list)
{
	if(list == nullptr || isCircular(list))
		return -1;
	
	int count = 0;
	while(list != nullptr)
	{
		count++;
		list = list->next;
	}
	return count;
}