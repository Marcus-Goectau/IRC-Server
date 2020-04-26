/*
 * linked_list.c
 * CS3337
 * Written by: Marcus Goeckner
 * 3/11/2020
 *
 * Basic functions for a generic singly-linked list
*/

#include "linked_list.h"
#include <stdlib.h>

/// adds a new node to the front of the list
/// \param head: the current head of the linked list
/// \param data: the data to be stored within the newly added node
void linked_list_push(struct LinkedListNode **head, void *data) {
    struct LinkedListNode *new_node = (struct LinkedListNode*)malloc(sizeof(struct LinkedListNode));
    new_node->data = data;
    new_node->next = *head;
    *head = new_node; // set this node to be the bew current head
}

/// gets the next node in a list
/// \param node: the current node from which the succeeding node is acquired from
/// \return: the next node in the list
struct LinkedListNode* linked_list_next(struct LinkedListNode *node) {
    return node->next;
}

/// finds and retrieves a specified node in a list
/// \param head: the current head of the linked list
/// \param data: the data of the node being searched for
/// \return: the node with the specified data, or NULL if the data is not found in the list
struct LinkedListNode* linked_list_get(struct LinkedListNode *head, void *data) {
    if (linked_list_size(head) == 0) { // if the list is empty return NULL
        return NULL;
    }

    struct LinkedListNode *current_node = head;
    while (current_node->data != data && current_node != NULL) { // search the list for the node containing data
        current_node = current_node->next;
    }

    if (current_node->data != data) { // if the list does not contain the data, return NULL
        return NULL;
    }

    return current_node;
}

/// finds and deletes a node from a list
/// \param head: the current head of the list
/// \param node: node to delete
void linked_list_delete(struct LinkedListNode **head, struct LinkedListNode *node) {
    struct LinkedListNode *currentNode = *head;

    if (*head == node) {
        *head = node->next;
        free(node);
        return;
    }

    while (currentNode != NULL && currentNode->next != node) {
        currentNode = currentNode->next;
    }

    if (currentNode != NULL) {
        currentNode->next = node->next; // set current node's next node to skip the node to be removed from the list
        free(node); // free the target node from the heap
    }
}

/// calculates the size of a linked list
/// \param head: the current head of the list
/// \return: the size of the list
int linked_list_size(struct LinkedListNode *head) {
    if (head == NULL) {
        return 0; // list is empty
    }

    struct LinkedListNode *currentNode = head;
    int size = 0;
    while (currentNode != NULL) {
        currentNode = currentNode->next;
        size++;
    }

    return size;
}
