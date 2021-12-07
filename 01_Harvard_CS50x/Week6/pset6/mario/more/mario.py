# Author: Jesus Carlos Martinez Gonzalez
# Date: 21/10/2021
# Objective: Print out an inverted pyramid of '#' based on a user input


def main():
    while True:
        size = input('Enter height of the pyramid: ')
        if size.isnumeric():
            size = int(size)
            if size <= 8 and size >= 1:
                break
    for i in range(size):
        print((' ' * (size - (i + 1))) + ('#' * (i + 1)) + '  ' + ('#' * (i + 1)))


if __name__ == "__main__":
    main()
