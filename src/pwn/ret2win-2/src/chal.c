#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// gcc chal.c -o chal -fPIE -pie -fstack-protector-all -fno-omit-frame-pointer -std=c17

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void banner() {
    printf("=====================================\n");
    printf("Welcome to the ret2win-2 Challenge!\n");
    printf("PIE and Canary are on. Find the leaks!\n");
    printf("=====================================\n");
}

void win() {
    system("cat /home/chal/flag.txt");
}

__attribute__((noinline))
static unsigned long leak_canary() {
    volatile unsigned long *rbp = (unsigned long *)__builtin_frame_address(0);
    return *(rbp - 1);
}

static void tour_booth() {
    puts("Tour booth: collect your security stamp and map pin.");
    printf("Security stamp: 0x%lx\n", leak_canary());
    printf("Map pin: %p\n", init);
}

int chal() {
    char buf[64];
    puts("Try to reach the win function!\n");
    tour_booth();
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
