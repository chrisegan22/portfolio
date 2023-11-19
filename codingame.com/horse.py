import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

n = int(input())
print(n,"1")
p = [0] * n
print(p,"2")
for i in range(n):
    print(i,"3")
    p[i] = int(input())
    print(p,"4")
p.sort()
print(p,"5")
D = sys.maxsize
print(D,"6")
for i in range(1,n):
    print(i,"7")
    D = min(D, p[i] - p[i - 1])


# Write an answer using print
# To debug: print("Debug messages...", file=sys.stderr, flush=True)


print(D)
