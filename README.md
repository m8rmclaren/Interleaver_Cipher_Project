# Intro to Cryptography: Interleaver Cipher Project
CS303 Project 1: Interleaver Cipher

Given an input txt file, read data, encrypt using interleaver cipher, and output to another txt file. Allocates dynamic 'array' used as matrix, using ```matrix[row*column_size+column)``` for matrix access.

Interleaver cipher creates cipher text by adding plaintext to n matrix columns (& 'm' rows based on size of plaintext), and then reads from the rows. Obviously, not very secure but good practice I suppose.

Input text is the entire bee movie script, don't sue me lol
