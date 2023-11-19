import sys
import math

# Don't let the machines win. You are humanity's last hope...

width = int(input())  # the number of cells on the X axis
print(width)
height = int(input())  # the number of cells on the Y axis
print(height)
for i in range(height):
    print(i)
    line = input()  # width characters, each either 0 or .
    print(line)
# Write an action using print
# To debug: print("Debug messages...", file=sys.stderr, flush=True)


# Three coordinates: a node, its right neighbor, its bottom neighbor
print("0 0 1 0 0 1")
print("1 0 -1 -1 -1 -1")
print("0 1 -1 -1 -1 -1")
