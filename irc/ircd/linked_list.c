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

/// adds a new node to the front of a list
/// \param head: the current head of the linked list
/// \param data: the data to be stored within the newly added node
void linked_list_push(struct linked_list_node **head, void *data) {
    struct linked_list_node *node = (struct linked_list_node*)malloc(sizeof(struct linked_list_node));
    node->next = *head;
    node->data = data;
    *head = node; // set this node to be the new current head
}

/// gets the next node in a list
/// \param node: the current node from which the succeeding node is acquired from
/// \return: the next node in the list
struct linked_list_node* linked_list_next(struct linked_list_node *node) {
    return node->next;
}

/// finds and retrieves a specified node in a list
/// \param head: the current head of the linked list
/// \param data: the data of the node being searched for
/// \return: the node with the specified data, or NULL if the data is not found in the list
struct linked_list_node* linked_list_get(struct linked_list_node *head, void *data) {
    if (linked_list_size(head) == 0) { // if the list is empty return NULL
        return NULL;
    }

    struct linked_list_node *currentNode = head;
    while (currentNode->data != data && currentNode != NULL) { // search the list for the node containing data
        currentNode = currentNode->next;
    }

    if (currentNode->data != data) { // if the list does not contain the data, return a NULL
        return NULL;
    }

    return currentNode;
}

/// finds and deletes a node from a list
/// \param head: the current head of the list
/// \param node: node to delete
void linked_list_delete(struct linked_list_node *head, struct linked_list_node *node) {
    struct linked_list_node *currentNode = head;
    while (currentNode->next != node && currentNode != NULL) {
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
int linked_list_size(struct linked_list_node *head) {
    if (head == NULL) {
        return 0; // list is empty
    }

    struct linked_list_node *currentNode = head;
    int size = 0;
    while (currentNode != NULL) {
        size++;
        currentNode = currentNode->next;
    }

    return size;
}
