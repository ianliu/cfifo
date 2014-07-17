# Circular FIFO in C

This is a very small implementation of a circular FIFO structure in C.
To use it just copy the cfifo.c and cfifo.h files into your project
directory. No special flags are required to compile cfifo.

# Usage example

## Storing a simple value

```C
#include <stdio.h>
#include "cfifo.h"

int main()
{
	int el;
	struct cfifo f;
	cfifo_init(&f, sizeof(int), 5);

	el = 1, cfifo_push(&f, &el);
	el = 2, cfifo_push(&f, &el);
	el = 3, cfifo_push(&f, &el);
	el = 4, cfifo_push(&f, &el);
	el = 5, cfifo_push(&f, &el);
	el = 6, cfifo_push(&f, &el); // This one overwrites el = 1

	cfifo_pop(&f, &el), printf("%d\n", el); // 2
	cfifo_pop(&f, &el), printf("%d\n", el); // 3
	cfifo_pop(&f, &el), printf("%d\n", el); // 4
	cfifo_pop(&f, &el), printf("%d\n", el); // 5
	cfifo_pop(&f, &el), printf("%d\n", el); // 6

	return 0;
}
```

## Storing pointers

One aspect of the previous method is that elements where copied into
cfifo. What if we wanted to store a reference so we can modify the
elements from another location or save precious bits? We just need to
initialize cfifo to hold pointer values:

```C
cfifo_init(&fifo, sizeof(void*), 5);

while (some_condition) {
	struct BIG *foo = malloc(sizeof(BIG));
	cfifo_push(&fifo, &foo);
}
```

Now only the _pointer_ is copied into cfifo, not the whole structure.
