/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author XXX <XXX@andrew.cmu.edu>
 */

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = (queue_t *)malloc(sizeof(queue_t));

    /* What if malloc returned NULL? */
    if (q == NULL) {
        printf("queue_new error: malloc returned NULL\n");
        return NULL;
    }

    q->head = NULL;
    q->q_size = 0;
    q->tail = NULL;
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL) {
        printf("queue_free error: q is NULL\n");
        return;
    }
    while (q->head != NULL) {
        char *buf = NULL;
        queue_remove_head(q, buf, 1);
    }
    free(q);
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    if (q == NULL) {
        printf("queue_insert_head error: q is NULL\n");
        return false;
    }

    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = (list_ele_t *)malloc(sizeof(list_ele_t));
    /* What if either call to malloc returns NULL? */
    if (newh == NULL) {
        printf("queue_insert_head error: malloc returned NULL\n");
        return false;
    }

    size_t lengthS = strlen(s);

    newh->value = (char *)malloc(sizeof(char) * (lengthS + (size_t)1));
    /* Don't forget to allocate space for the string and copy it */
    strncpy(newh->value, s, lengthS);

    newh->value[lengthS] = '\0';

    /* Pointers processing */
    if (q->head == NULL)
        q->tail = newh;
    newh->next = q->head;
    q->head = newh;
    q->q_size++;
    // printf("tail: %s\n", q->tail->value);
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        printf("queue_insert_tail error: q is NULL\n");
        return false;
    }

    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = (list_ele_t *)malloc(sizeof(list_ele_t));

    if (newh == NULL) {
        printf("queue_insert_tail error: newh is NULL\n");
        return false;
    }

    /* Don't forget to allocate space for the string and copy it */
    size_t lengthS = strlen(s);
    newh->value = (char *)malloc(sizeof(char) * (lengthS + (size_t)1));
    if (newh->value == NULL) {
        printf("queue_insert_tail error: newh->value is NULL\n");
        return false;
    }

    strncpy(newh->value, s, lengthS);
    newh->value[lengthS] = '\0';
    newh->next = NULL;

    /*Tail processing*/
    if (q->q_size == 0) {
        q->head = newh;
        q->tail = newh;
    } else {
        q->tail->next = newh;
        q->tail = newh;
    }
    q->q_size++;
    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. */

    if (q == NULL) {
        printf("queue_remove_head error: q is NULL\n");
        return false;
    }

    if (q->head == NULL) {
        printf("queue_remove_head error: q has no elements attached\n");
        return false;
    }
    list_ele_t *delElement = q->head;

    if (buf != NULL) {
        strncpy(buf, delElement->value, bufsize - (unsigned long)1);
        buf[bufsize - 1] = '\0';
    }
    free(delElement->value);
    q->head = q->head->next;
    free(delElement);
    q->q_size--;
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL || q->head == NULL)
        return 0;
    return q->q_size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */
    if (q == NULL) {
        printf("queue_reverse error: q is NULL\n");
        return;
    }

    if (q->head == NULL) {
        printf("queue_reverse error: q is empty\n");
        return;
    }

    q->tail = q->head;

    list_ele_t *pre = NULL;
    list_ele_t *next = NULL;

    while (q->head != NULL) {
        next = q->head->next;
        q->head->next = pre;
        pre = q->head;
        q->head = next;
    }

    q->head = pre;
}
