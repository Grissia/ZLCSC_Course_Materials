#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// gcc chal.c -o chal -no-pie -fno-stack-protector -fno-omit-frame-pointer -std=c17

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void banner() {
    printf("=====================================\n");
    printf("Welcome to the ret2libc-0 Challenge!\n");
    printf("Two-stage overflow, one shell.\n");
    printf("=====================================\n");
}

__attribute__((naked))
void pop_rdi_ret() {
    __asm__("pop %rdi; ret");
}

int chal() {
    char buf[64];
    puts("Stage 1: leak libc address.");
    puts("Stage 2: call system('/bin/sh').");
    printf("Input your data: ");
    read(0, buf, 512);
    return 0;
}

int main() {
    init();
    banner();
    puts("Gift: there is a pop rdi; ret gadget in this binary.");
    while (1) {
        chal();
    }
    return 0;
}
