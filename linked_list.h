#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct linked_list
{
	char *data;
	int index; /* position of the element in the list, normally not used with Linked Lists, just for exercise */
	struct linked_list *next;
	struct linked_list *prev;
};
typedef struct linked_list linked_list;

// basic
int add_to_list(linked_list *list, char *string);
int display_item(linked_list *list);
int display_list(linked_list *list);
linked_list *search_from_list(linked_list *list, char *string);
int delete_from_list(linked_list *list, int index);

// additional
int empty_list(linked_list *list);
int swap_items(linked_list *node_1, linked_list *node_2);
int sort_list(linked_list *list);
int linkedlist_status(linked_list *list);

#endif