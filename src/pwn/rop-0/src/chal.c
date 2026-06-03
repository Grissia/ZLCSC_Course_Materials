#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// gcc chal.c -o chal -static -no-pie -fno-stack-protector -fno-omit-frame-pointer -std=c17

static const char binsh[] = "/bin/sh";

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void banner() {
    printf("=====================================\n");
    printf("Welcome to the rop-0 Challenge!\n");
    printf("No win function. Call execve.\n");
    printf("=====================================\n");
}

int chal() {
    char buf[64];
    puts("Hint: /bin/sh is inside the binary.");
    printf("/bin/sh address: %p\n", binsh);
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
