#include <stdio.h>

int* f()
{
    return (int *)12;
}

void print(int *v)
{
    printf("value=%d\n", *v);  // *12 fails here
}

int main()
{
    print(f());
}
