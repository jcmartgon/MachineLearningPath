# Author: Jesus Carlos Martinez Gonzalez
# Date: 23/10/2021
# Objective: Print whether the input number corresponds to a Visa, Mastercard or American Express card


# Performs the checksum validation over the passed argument
def check_sum(number):
    total = 0
    pos = 1
    curr = 0
    for i in reversed(number):
        curr = int(i)
        if pos % 2 == 0:
            curr *= 2
        for j in str(curr):
            total += int(j)
        pos += 1
    if total % 10 == 0:
        return True
    return False


# Validates the card given the argument
def card_type(number):
    if check_sum(number):
        if len(number) == 15 and number[0:2] in ['35', '37']:
            return('AMEX')
        elif len(number) == 16 and number[0:2] in ['51', '52', '53', '54', '55']:
            return('MASTERCARD')
        elif (len(number) == 13 or len(number) == 16) and number[0] == '4':
            return('VISA')
        else: 
            return('INVALID')
    else:
        return('INVALID')
    

def main():
    while True:
        number = input('Enter the card number: ')
        if number.isnumeric():
            break
    print(card_type(number))


if __name__ == "__main__":
    main()