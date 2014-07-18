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

#include "cfifo.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void cfifo_init(struct cfifo *cfifo, size_t sz, size_t cap)
{
	cfifo->cap = cap;
	cfifo->h = cfifo->len = 0;
	cfifo->sz = sz;
	cfifo->ptr = malloc(sz * cap);
}

void cfifo_free(struct cfifo *cfifo)
{
	free(cfifo->ptr);
}

int cfifo_isfull(struct cfifo *cfifo)
{
	return cfifo->len == cfifo->cap;
}

int cfifo_isempty(struct cfifo *cfifo)
{
	return cfifo->len == 0;
}

void cfifo_push(struct cfifo *cfifo, void *el)
{
	void *pos;
	if (cfifo->len == cfifo->cap) {
		pos = (char*)cfifo->ptr + cfifo->h * cfifo->sz;
		cfifo->h++;
		if (cfifo->h == cfifo->cap)
			cfifo->h = 0;
	} else {
		size_t offset = (cfifo->h + cfifo->len) % cfifo->cap;
		pos = (char*)cfifo->ptr + offset * cfifo->sz;
		cfifo->len++;
	}

	memcpy(pos, el, cfifo->sz);
}

int cfifo_pop(struct cfifo *cfifo, void *el)
{
	size_t offset;
	if (cfifo->len == 0)
		return 0;
	offset = cfifo->h * cfifo->sz;
	memcpy(el, (char*)cfifo->ptr + offset, cfifo->sz);
	cfifo->h++;
	if (cfifo->h == cfifo->cap)
		cfifo->h = 0;
	cfifo->len--;
	return 1;
}
