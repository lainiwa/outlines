#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(int c, const char **v)
{
    char buf[1000];
    size_t sz = 0;

    if( c != 2) {
        printf("\nPlease call\n\t%s filename\n", v[0]);
        return 1;
    }

    // int fd = open(v[1], O_RDONLY|);
    // int fd = open(v[1], O_RDONLY|O_NOFOLLOW);  // Don't follow soft links
    int fd = open(v[1], O_RDONLY|O_PATH);  // Open soft links files,
                                           // rather than where they point at
    perror("fd");
    printf("fd = %d\n", fd);
    sz = read(fd, buf, 1000);

    printf("sz = %ld\n", sz);
}
