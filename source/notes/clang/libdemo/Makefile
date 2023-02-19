
all: hello

hello: main.c hello.h libHello.so
	gcc main.c -L. -lHello -o hello

libHello.so: hello.h hello.c
	gcc -o libHello.so -shared hello.c

clean:
	-rm hello libHello.so *.o 2>/dev/null
