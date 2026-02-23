; nasm -f elf64 helloworld.asm -o helloworld.o
; ld helloworld.o -o helloworld.out

section .data
    msg db "Hello World!\n", 0
    msglen equ $ - msg

section .text
    global _start

_start:
    ; write(1, msg, msglen)
    mov rax, 1      ; sys_write
    mov rdi, 1      ; stdout
    mov rsi, msg    ; message address
    mov rdx, msglen ; message length
    syscall         ; invoke system call

    ; exit(0)
    mov rax, 60     ; sys_exit
    xor rdi, rdi    ; status 0
    syscall         ; invoke system call
