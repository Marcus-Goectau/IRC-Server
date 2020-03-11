/*
 * linked_list.h
 * CS3337
 * Written by: Marcus Goeckner
 * 3/10/2020
 *
 * Header file for linked_list data structure
*/

#ifndef IRCD_LINKED_LIST_H
#define IRCD_LINKED_LIST_H

struct LinkedListNode {
	struct LinkedListNode *next;
	void *data;
};

void linked_list_push(struct LinkedListNode **head, void *data);

struct LinkedListNode* linked_list_next(struct LinkedListNode *node);

struct LinkedListNode* linked_list_get(struct LinkedListNode *head, void *data);

void linked_list_delete(struct LinkedListNode *head, struct LinkedListNode *node);

int linked_list_size(struct LinkedListNode *head);

#endif //IRCD_LINKED_LIST_H