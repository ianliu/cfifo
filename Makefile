
test: test-cfifo
	@echo -n 'Executing test-cfifo...'
	@if test ./test-cfifo; then \
	  echo ' OK'; \
	else \
	  echo ' FAIL'; \
	fi

test-cfifo: test-cfifo.c cfifo.c
	# Using very restrictive flags to guarantee compatibility. You
	# don't need these flags to compile.
	gcc -Wall -Wextra -Werror -ansi -pedantic -o $@ $^

clean:
	rm -f test-cfifo
