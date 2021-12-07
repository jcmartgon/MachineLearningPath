# Author: Jesus Carlos Martinez Gonzalez
# Date: 24/10/2021
# Objective: Identify whether or not a dna-sequence matches someone within a group


import sys
import csv


# Returns the lonest subsequence within a sequence
def longest_sequence(seq, pattern):
    tmp = [0] * len(seq)
    for i in range(len(seq) - len(pattern), -1, -1):
        if seq[i: i + len(pattern)] == pattern:
            if i + len(pattern) > len(seq) - 1:
                tmp[i] = 1
            else:
                tmp[i] = 1 + tmp[i + len(pattern)]
    return max(tmp)


def main():
    
    # Ensure proper usage
    if len(sys.argv) != 3:
        sys.exit(f'Usage: python dna.py FILE-WITH-STR-COUNTS FILE-WITH-DNA-SEQUENCES')
    
    # To keep track of data
    people = {}
    matches = []
    
    csv_file = open(sys.argv[1], 'r')  # file with people's names and their str-counts
    
    # Stores valuable information from the file into memory
    for i, row in enumerate(csv_file):
        rows = row.strip().split(',')
        if (i == 0):
            patterns = rows[1:]
        else:
            people[rows[0]] = [int(counts) for counts in rows[1:]]
            
    sequence = open(sys.argv[2], 'r').read()  # file with the dna sequence to analyze

    for i in range(len(patterns)):
        matches.append(longest_sequence(sequence, patterns[i]))
    
    # Compare people's information with what was found during sequence analysis
    for name, data in people.items():
        if data == matches:
            print(name)
            exit(0)
    
    print('No match')


if __name__ == "__main__":
    main()