# defining main
def main():
    height = get_height()
    left = height - 1
    heights = int(1)

    # looping through the range of height
    for __ in range(height):
        # Adding spaces to the left of blocks
        print(left * " ", end="")
        left -= 1
# Adding blocks
        print(heights * "#")
        heights += 1

# Defining get height function to get the height from user


def get_height():
    # Checking to see if conditions are met
    while True:
        try:
            n = int(input("Please enter a positive integer between 1 - 8: "))
            if n > 0:
                if n < 9:
                    return n
        # Checking for non integer
        except ValueError:
            print("Not a correct range of integer!")


main()