#include <assert.h>
#include "cfifo.h"

int main()
{
	struct cfifo f;
	cfifo_init(&f, sizeof(int), 5);

	/* Initialization assertions */
	assert(f.cap == 5);
	assert(f.h == 0);
	assert(f.len == 0);
	assert(f.sz == sizeof(int));
	assert(f.ptr != 0);
	assert(cfifo_isempty(&f));
	assert(!cfifo_isfull(&f));

	/* After one push */
	int el, t;
	el = 1, cfifo_push(&f, &el);
	assert(f.len == 1);
	assert(!cfifo_isempty(&f));
	assert(!cfifo_isfull(&f));

	/* After one pop */
	cfifo_pop(&f, &t);
	assert(el == t);
	assert(f.len == 0);
	assert(f.h == 1);
	assert(cfifo_isempty(&f));

	/* Push until full */
	el = 1, cfifo_push(&f, &el);
	el = 2, cfifo_push(&f, &el);
	el = 3, cfifo_push(&f, &el);
	el = 4, cfifo_push(&f, &el);
	el = 5, cfifo_push(&f, &el);
	assert(cfifo_isfull(&f));
	assert(!cfifo_isempty(&f));

	/* Push to overwrite head */
	el = 6, cfifo_push(&f, &el);
	assert(cfifo_isfull(&f));
	assert(!cfifo_isempty(&f));

	/* Pop until empty */
	cfifo_pop(&f, &el), assert(el == 2);
	cfifo_pop(&f, &el), assert(el == 3);
	cfifo_pop(&f, &el), assert(el == 4);
	cfifo_pop(&f, &el), assert(el == 5);
	cfifo_pop(&f, &el), assert(el == 6);
	assert(cfifo_isempty(&f));
	assert(!cfifo_isfull(&f));

	return 0;
}
