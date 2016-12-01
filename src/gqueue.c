#include "gqueue.h"

gqueue_t *new_gqueue_t(int ini_size, int el_size) {
	// allocate queue object
	gqueue_t *q = malloc(sizeof(gqueue_t));
	if( q == NULL )
		return NULL;
	// The user must provide the size of each queue element
	q->size = ini_size ? ini_size : 1;
	q->buf = malloc(q->size	* el_size);
	if(q->buf == NULL ) {
		free(q);
		return NULL;
	}
	// initialize state of queue
	q->in = q->out = q->count = 0;
	q->el_size = el_size;
	return q;
}
void delete_gqueue_t(gqueue_t *q) {
	free(q->buf);
	free(q);
}

int is_empty_gqueue(gqueue_t *q) {
	return q->count == 0;
}

int is_full_gqueue(gqueue_t *q) {
	return q->count == q->size;
}

int put_gqueue(gqueue_t	*q, void* el) {
	if( is_full_gqueue(q) )
		return -1;
	// memcpy(dst, src, n_bytes): memory copy
	// must do pointer arithmetic explicitly
	memcpy(q->buf + q->in*q->el_size, el, q->el_size);
	q->in = (q->in + 1) % q->size;
	q->count++;
	return 0;
}
int get_gqueue(gqueue_t *q, void*el) {
	if( is_empty_gqueue(q) )
		return -1;
	memcpy(el, q->buf + q->out*q->el_size, q->el_size);
	q->out = (q->out + 1) % q->size;
	q->count--;
	return 0;
}

int get_front(gqueue_t *q, void*el)
{
	if( is_empty_gqueue(q) )
			return -1;
	memcpy(el, q->buf + q->out*q->el_size, q->el_size);
	return 0;
}

// private: can be invoked only in queue.c
/*static void adjust_gqueue(gqueue_t* q) {
	q->in %= q->size;
	q->out %= q->size;
}
static int resize_gqueue(gqueue_t* q) {
	int	*p = (void *)realloc(q->buf, 2 * (q->size) * (q->el_size));
	int i;
	if( p == NULL )
		return -1;
	q->buf = p;
	for( i = 0; i < q->in; i++)
		q->buf[q->size + i] = q->buf[i];
	q->in += q->size;
	q->size *= 2;
	return 0;
}*/
