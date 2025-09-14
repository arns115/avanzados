m, n, p = map(int, input().split())
num=1
den=m
import math

import sys

if n == 0 and p == 0:
    print("1/1")
    sys.exit()


for i in range(p - 1, 0, -1):
  num *= i
  den *= m - (p - i)
  aux = math.gcd(num, den)
  num //= aux
  den //= aux
num *= 2
aux = math.gcd(num, den)
num //= aux
den //= aux

num *= n
aux = math.gcd(num, den)
num //= aux
den //= aux

tot = 0
for i in range(n):
  if p - n - i < 0:
    break
  x = math.comb(n - 1,i) * (1 << (n - 1 - i)) * math.comb(m - 2 * n, (p - n - i))
  # print(x)
  tot += x

# print(tot)
aux = math.gcd(tot, den)
tot //= aux
den //= aux

print(f"{num * tot}/{den}")
