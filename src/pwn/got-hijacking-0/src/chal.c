#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// gcc chal.c -o chal -no-pie -fno-stack-protector -Wl,-z,norelro -std=c17

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void banner() {
    printf("=====================================\n");
    printf("Welcome to the got-hijacking-0 Challenge!\n");
    printf("Hijack puts, then get a shell.\n");
    printf("=====================================\n");
}

void setup() {
    system("echo setup > /dev/null");
}

int chal() {
    uintptr_t addr;
    uintptr_t value;
    char buf[64];

    puts("You can write one 8-byte value to any address.");
    puts("Then we will call puts() with your input.");
    printf("Address to write: ");
    scanf("%lx", &addr);
    printf("Value to write: ");
    scanf("%lx", &value);

    *(uintptr_t *)addr = value;
    printf("echo> ");
    scanf("%63s", buf);
    puts(buf);
    return 0;
}

int main() {
    init();
    banner();
    chal();
    return 0;
}
