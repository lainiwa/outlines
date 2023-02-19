
all: hello ltrace strace

hello: main.c
	gcc main.c -z lazy -o hello

ltrace:
	@echo '============LTRACE============' >&2
	ltrace ./hello

strace:
	@echo '============STRACE============' >&2
	strace ./hello

clean:
	-rm hello libHello.so *.o 2>/dev/null
