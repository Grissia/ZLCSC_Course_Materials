#include <stdio.h>
#include <limits.h>

void print_binary(int value) {
    const unsigned char *bytes = (const unsigned char *)&value;
    for (int byte = (int)sizeof(int) - 1; byte >= 0; --byte) {
        for (int bit = 7; bit >= 0; --bit) {
            putchar((bytes[byte] >> bit) & 1 ? '1' : '0');
        }
        putchar(' ');
    }
}

int main() {
    int a = INT_MAX;
    printf("Value of a: dec=%d, hex=%x\n", a, a);
    print_binary(a);
    printf("\n\n");
    a += 1;
    printf("Value of a: dec=%d, hex=%x\n", a, a);
    print_binary(a);
    printf("\n\n");

    int b = 0xFFFFFFFF;
    printf("Value of b: dec=%d, hex=%x\n", b, b);
    print_binary(b);
    printf("\n\n");
    b += 1;
    printf("Value of b: dec=%d, hex=%x\n", b, b);
    print_binary(b);
    printf("\n");

    return 0;
}