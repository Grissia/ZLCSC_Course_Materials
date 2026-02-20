#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

// gcc chal.c -o chal -no-pie -fno-stack-protector -std=c17

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void banner() {
    printf("=====================================\n");
    printf("Welcome to the ret2win Challenge!\n");
    printf("Try to overflow the buffer!\n");
    printf("=====================================\n");
}

void win() {
    system("cat /home/chal/flag.txt");
}

int chal() {
    char buf[64];
    printf("Try to find the win function!\n");
    printf("An opportunity to read the flag is waiting for you!\n");
    printf("Input your data: ");
    fgets(buf, 512, stdin);
    return 0;
}

int main() {
    init();
    banner();
    chal();
    return 0;
}