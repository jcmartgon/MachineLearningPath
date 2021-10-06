# Substitution cipher

Given a substitution cipher key and a plaintext, output the ciphertext.

## Running

To run:
1. Make sure you've got a C compiler installed
2. Use the "./substitution __*key*__" command

## Restrictions

- The key must be made up of only alphabetical values
- The key must be made up entirely of unique characters
- The key must be made up of exactly 26 characters (one for each letter in the latin alphabet)
- The key is not case-sensitive

## Technology stack

The C library "cs50.h" was used for educational purposes to assist with input fetching.
The C library "ctype.h" was used to access case-based functions.
The C library "string.h" was used to acces strlen().