#ifndef HELPER_H
#define HELPER_H

struct linked_list;
typedef struct linked_list linked_list;

linked_list *generateNode(int index, int data);
linked_list *generateNodeWithData(int index, char const *data);
void freeNode(linked_list *node);
bool checkNode(linked_list *node, int index, char const *data, linked_list *prev, linked_list *next);
void linkNodes(linked_list **prev_node, linked_list **next_node);

#endif