#include <stdio.h>

// gcc chal.c -o chal -std=c17

int buf[] = {71, 115, 107, 112, 119, 108, 103, 124, 77, 61, 121, 114, 83, 117, 62, 125, 79, 101, 119, 80, 124, 104};

void print_flag(){
    for(int i = 0; i < sizeof(buf)/sizeof(int); i++){
        printf("%c", buf[i]^i);
    }
}

int main(){
    printf("Where is the flag???\n");
    return 0;
}