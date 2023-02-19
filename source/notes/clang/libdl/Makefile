
all: hello libHello.so

hello: main.c
	gcc main.c -ldl -o hello

libHello.so: hello.c
	gcc -o libHello.so -shared hello.c

clean:
	-rm hello libHello.so *.o 2>/dev/null
