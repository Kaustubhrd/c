
import math

prefix = 24
subnets = 2

new_prefix = prefix + math.ceil(math.log2(subnets))
total_hosts = 2 ** (32 - new_prefix)

mask = (0xFFFFFFFF << (32 - new_prefix)) & 0xFFFFFFFF

print("Subnet Mask:", (mask >> 24) & 255, ".",
      (mask >> 16) & 255, ".",
      (mask >> 8) & 255, ".",
      mask & 255, sep="")

print("Usable hosts per subnet:", total_hosts - 2)

print("\nSubnet 1: 192.168.1.0/25")
print("Subnet 2: 192.168.1.128/25")
