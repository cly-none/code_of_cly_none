#!/bin/python

from math import *
from sympy import *

MOD = 1000000000

def main():
    n = int(input())
    lim = 0
    ans = 0
    while 2 ** (lim + 1) <= n:
        lim = lim + 1
    # print 'lim', lim
    dp = [0] * (lim + 10)
    rec = [0] * (lim + 10)
    for i in range(1, lim+1):
        t = int(pow(n, 1.0 / i))
        while (t+1) ** i <= n:
            t = t + 1
        rec[i] = (t - 1) * (t - 1) % MOD
        # print 'rec', i, ': ', rec[i]
    for i in range(1, lim+1):
        for j in range(i, lim+1, i):
            dp[i] = (dp[i] + mobius(j / i) * rec[j]) % MOD
    dp1 = [0] * (lim + 10)
    rec1 = [0] * (lim + 10)
    for i in range(1, lim+1):
        t = int(pow(n, 1.0 / i))
        while (t+1) ** i <= n:
            t = t + 1
        rec1[i] = t - 1
    for i in range(1, lim+1):
        for j in range(i, lim+1, i):
            dp1[i] = (dp1[i] + mobius(j / i) * rec1[j]) % MOD

    ans = dp[1]
    # print 'ans1', ans
    for a in range(1, lim+1):
        for b in range(1, lim+1):
            if gcd(a,b) != 1:
                continue
            v = max(a,b)
            ans = (ans - (dp1[v] - 1)) % MOD
    ans = (ans % MOD + MOD) % MOD
    print ans

main()
