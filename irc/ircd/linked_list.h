/*
 * linked_list.h
 * CS3337
 * Written by: Marcus Goeckner
 * 3/10/2020
 *
 * Header file for linked_list data structure
*/

struct linked_list_node {
	struct linked_list_node *next;
	void *data;
};

void linked_list_push(struct linked_list_node **head, void *data);

struct linked_list_node* linked_list_next(struct linked_list_node *node);

struct linked_list_node* linked_list_get(struct linked_list_node *head, void *data);

void linked_list_delete(struct linked_list_node *head, struct linked_list_node *node);

int linked_list_size(struct linked_list_node *head);
