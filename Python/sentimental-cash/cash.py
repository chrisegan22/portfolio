from cs50 import get_float
# Asking user to add change and checking if it meets the condition
while True:
    change = get_float("Change owed: ")
    if (change >= 0):
        break

change = round(change * 100)

count = 0
# counting how many 25 cents is there in change
while (change >= 25):
    change = change - 25
    count += 1
    # print(count, change)
# counting how many 10 cents is there in change
while (change >= 10):
    change = change - 10
    count += 1
    # print(count, change)
# counting how many 5 cents is there in change
while (change >= 5):
    change = change - 5
    count += 1
    # print(count, change)
# counting how many 1 cent is there in change
while (change >= 1):
    change = change - 1
    count += 1
    # print(count, change)
# printing the counted coins
print(count)

# was thinking to difficult with this program