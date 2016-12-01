#ifndef __GQUEUE_H
#define __GQUEUE_H

#include <stdio.h>
#include <stdlib.h>



/** @defgroup gqueue gqueue
 * @{
 *
 * Declaration of the functions to use with queues
 */


typedef struct gqueue_t{
	void *buf;          // pointer to array that stores queue elements
	int in,out;        // indices of the array pointed by buf to insert/remove elements
	int size;         // size of the array
	int count;         // number of elements in queue
	int el_size;       //for pointer arithmetic
	int front;			//indice of the first element

} gqueue_t;

gqueue_t *new_gqueue_t(int ini_size, int el_size);

void delete_gqueue(gqueue_t *q);

int is_empty_gqueue(gqueue_t *q);

int is_full_gqueue(gqueue_t *q);

int put_gqueue(gqueue_t	*q, void* el);

int get_gqueue(gqueue_t *q, void*el);

int get_front(gqueue_t *q, void*el)

static void adjust_gqueue(gqueue_t *q);

static int resize_gqueue(gqueue_t	*q);


#endif
