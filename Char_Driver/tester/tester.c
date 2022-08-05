#include <stdio.h>
#include <stdlib.h>

int main() {

    char buffer[1024]; 

    int ret; 
    FILE *file = fopen("/dev/chamur", "r+");

    ret = fputs("hello world", file);

    // get the file pointer
    int fd = fileno(file); 

    // read from the device driver 
    ret = read(fd, buffer, 1024);

    printf("Size of char: %d\n", sizeof(char));
    printf("Thing: %d\n", ret);
    printf(buffer);

    fclose(file);

    return 0; 
}