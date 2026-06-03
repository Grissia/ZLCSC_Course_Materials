#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// gcc chal.c -o chal -no-pie -fno-stack-protector -z execstack -fno-omit-frame-pointer -std=c17

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void banner() {
    printf("=====================================\n");
    printf("Welcome to the ret2sc-0 Challenge!\n");
    printf("The simplest ret2sc.\n");
    printf("=====================================\n");
}

int chal() {
    char buf[64];
    printf("Buffer address: %p\n", buf);
    printf("Input your data: ");
    read(0, buf, 512);
    return 0;
}

int main() {
    init();
    banner();
    chal();
    return 0;
}
