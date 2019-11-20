[![Build Status](https://api.travis-ci.com/nnminh171298/VAMK-Linked-List.svg?token=MF5xcGDYyi6pXxwn5xNf&branch=master)](https://travis-ci.com/nnminh171298/VAMK-Linked-List) [![Coverage Status](https://coveralls.io/repos/github/nnminh171298/VAMK-Linked-List/badge.svg?branch=master)](https://coveralls.io/github/nnminh171298/VAMK-Linked-List?branch=master)
# VAMK Linked List
My C implementation of a linked list, made during the course embedded system programming at VAMK
# Specification
All functions (except display item) expects to get the head of the list as a parameter  
All functions will return -1 as an error, if linked list pointer is NULL  
```cpp
int add_to_list(linked_list *list, char *string);
```
* Will create a new list item and add that to end of the list
* Will create a new element (malloc)
* Write new index (last+1) to new elements index
* Linked list pointer is pointing to head/last element of the list
* Return: -1 as error (no space left), index position in success
```cpp
int display_item(linked_list *list);
```
* Displays the required element
* Return: -1 element not found, 0 ok
```cpp
int display_list(linked_list *list);
```
* List all elements in a list
* Return: number of elements in list
```cpp
linked_list *search_from_list(linked_list *list, char *string);
```
* Search for data from a list
* Return: NULL if not found
```cpp
int delete_from_list(linked_list *list, int index);
```
* Delete item from a list and free space
* Rest of list items index will be decremented
* Return value: -1 on error, otherwise length of remaining list
