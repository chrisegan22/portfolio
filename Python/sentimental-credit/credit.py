from cs50 import get_int

# Main function


def main():
    while True:
        # Getting number from user
        credit_card = get_int("Number: ")
        if credit_card >= 0:
            break
# checking card number
    if validity_checker(credit_card):
        # Printing name of card
        print_credit_card_name(credit_card)
    else:
        print("INVALID")


def validity_checker(ccnum):
    # Checking which card it is and if valid
    return checksum(ccnum)

# luhn algorithm


def checksum(ccnum):
    sum = 0
    for i in range(len(str(ccnum))):
        if (i % 2 == 0):
            sum += ccnum % 10
        else:
            digit = 2 * (ccnum % 10)
            sum += digit // 10 + digit % 10

        ccnum //= 10

    return sum % 10 == 0

# Printing name or INVALID


def print_credit_card_name(ccnum):
    if (ccnum >= 34e13 and ccnum < 35e13) or (ccnum >= 37e13 and ccnum < 38e13):
        print("AMEX")

    elif (ccnum >= 51e14 and ccnum < 56e14):
        print("MASTERCARD")

    elif (ccnum >= 4e12 and ccnum < 5e12) or (ccnum >= 4e15 and ccnum < 5e15):
        print("VISA")

    else:
        print("INVALID")


# Main function
if __name__ == "__main__":
    main()