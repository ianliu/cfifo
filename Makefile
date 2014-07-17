
test: test-cfifo
	@echo -n 'Executing test-cfifo...'
	@if test ./test-cfifo; then \
	  echo ' OK'; \
	else \
	  echo ' FAIL'; \
	fi

test-cfifo: test-cfifo.c cfifo.c
	gcc -o $@ $^

clean:
	rm -f test-cfifo
