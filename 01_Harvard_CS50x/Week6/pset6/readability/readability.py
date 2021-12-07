# Author: Jesus Carlos Martinez Gonzalez
# Date: 23/10/2021
# Objective: Determine a given text's readability level based on US scholar years


# Analyzes the argument text and returns the corresponding grade
def grade(text):
    letters = 0
    words = 0
    sentences = 0
    for char in text:
        if char == ' ':
            words += 1
        elif char == '.' or char == '?' or char == '!':
            sentences += 1
        elif char.isalpha():
            letters += 1
    words += 1
    grade = round(0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8)
    if grade < 1:
        return 'Before Grade 1'
    elif grade >= 16:
        return 'Grade 16+'
    else:
        return f'Grade {grade}'


def main():
    text = input('Text: ')
    print(grade(text))


if __name__ == "__main__":
    main()