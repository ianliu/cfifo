/*
 * Copyright 2014 Ian Liu Rodrigues <ian.liu88@gmail.com>
 *
 * This file is part of CFIFO.
 * 
 * Foobar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CFIFO_H__
#define __CFIFO_H__

#include <stdlib.h>

/* You may find more information at http://github.com/ianliu/cfifo */

/* Copy cfifo.c and cfifo.h into your project and compile cfifo.c. No special
 * flags needed.
 */

/* Usage examples:
 *
 * #include "cfifo.h"
 *
 * int main()
 * {
 *     int el;
 *     struct cfifo f;
 *     cfifo_init(&f, sizeof(int), 5);
 *
 *     el = 1, cfifo_push(&f, &el);
 *     el = 2, cfifo_push(&f, &el);
 *     el = 3, cfifo_push(&f, &el);
 *     el = 4, cfifo_push(&f, &el);
 *     el = 5, cfifo_push(&f, &el);
 *     el = 6, cfifo_push(&f, &el); // This one overwrites el = 1
 *
 *     cfifo_pop(&f, &el), printf("%d\n", el); // 2
 *     cfifo_pop(&f, &el), printf("%d\n", el); // 3
 *     cfifo_pop(&f, &el), printf("%d\n", el); // 4
 *     cfifo_pop(&f, &el), printf("%d\n", el); // 5
 *     cfifo_pop(&f, &el), printf("%d\n", el); // 6
 *     cfifo_free(&f);
 *
 *     return 0;
 * }
 */

/* cfifo - Circular FIFO
 *
 * cap: capacity of this circular fifo
 * h:   index of the fifo's head
 * len: number of elements pushed into the fifo
 * sz:  size of one fifo element
 * ptr: pointer to the fifo's memory
 */
struct cfifo {
	size_t cap;
	size_t h;
	size_t len;
	size_t sz;
	void *ptr;
};

/* Initialize cfifo with capacity 'cap' and element size 'sz' */
void cfifo_init(struct cfifo *cfifo, size_t sz, size_t cap);

/* Frees internal pointer */
void cfifo_free(struct cfifo *cfifo);

/* Return 1 if fifo is full, 0 otherwise */
int cfifo_isfull(struct cfifo *cfifo);

/* Return 1 if fifo is empty, 0 otherwise */
int cfifo_isempty(struct cfifo *cfifo);

/* Pushes 'el' into 'cfifo'; if 'cfifo' is full overwrites the head
 * element. The element is copied into the structure. */
void cfifo_push(struct cfifo *cfifo, void *el);

/* Pops the first element of 'cfifo' and copies it into 'el'. 'el'
 * must have at least 'sz' bytes to hold the value. */
int cfifo_pop(struct cfifo *cfifo, void *el);

#endif /* __CFIFO_H__ */

