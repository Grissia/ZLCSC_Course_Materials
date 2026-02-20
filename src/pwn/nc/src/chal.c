#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// gcc chal.c -o chal -std=c17

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void banner() {
    printf("=====================================\n");
    printf("Welcome to the nc Challenge!\n");
    printf("It it glad to see you here!\n");
    printf("Let's read the flag for you:\n");
    printf("=====================================\n");
}

void chal() {
    FILE *f = fopen("/home/chal/flag.txt", "r");
    char buf[0x100] = {};
    assert(f != NULL);
    fread(buf, 1, sizeof(buf) - 1, f);
    fclose(f);
    printf("%s\n", buf);
}

int main() {
    init();
    banner();
    chal();
    return 0;
}