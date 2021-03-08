/*
Project: Interleaver Cipher
Description: Encrypt input file using interleaver cipher, and n columns, and output to file
HISTORY: Verson 1.0 2/18/2021
Copyright © 2021 Hayden Roszell. All rights reserved.
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string read_from_file(const string& filename);
string interleave_wbc(const string& plain_text, const int num_of_columns);
string interleave_wbr(const string& plain_text, const int num_of_columns);
bool write_to_file(const string& filename, const string& cipher_text);

int main() {
    string plaintext = read_from_file("/Users/haydenroszell/Documents/School/College/ERAU/Sophomore/sem2/CS303/projects/project1/input.txt");
    // Change file paths before you run on your computer
    int num_of_columns;
    cout << "Enter # of columns for interleaver: "; cin >> num_of_columns;
    //string cipher_text = interleave_wbc(plaintext, num_of_columns); // Uncomment for write by columns
    string cipher_text = interleave_wbr(plaintext, num_of_columns); // Uncomment for write by rows
    cout << cipher_text << endl;

    if (!write_to_file("/Users/haydenroszell/Documents/School/College/ERAU/Sophomore/sem2/CS303/projects/project1/output.txt", cipher_text))
        return 1;

    return 0;
}

string read_from_file(const string& filename) {
    fstream input (filename); // ios::in
    string data;
    string line;
    if (input.is_open()) {
        while (getline(input, line)) {
            data.append(line);
        }
        input.close();
    }
    else cout << "Something went wrong" << endl;
    for (int i = 0, length = data.size(); i < length; i++) {
        if (ispunct(data[i]) || data[i] == ' ') { // remove punctuation & spaces
            data.erase(i--, 1);
            length = data.size();
        }
        data[i] = toupper(data[i]);
    }
    return data;
}
// Interleave write by columns
string interleave_wbc(const string& plain_text, const int num_of_columns) {
    int num_of_rows = ceil(plain_text.size() / (double)num_of_columns); int count = 0;
    // Need to fill remainder of matrix with Z's
    auto *matrix = new char[num_of_columns*num_of_rows]; // large block of memory instead of dynamic # of column's
    for (int column = 0; column < num_of_columns; column++) {
        for (int row = 0; row < num_of_rows; row++) {
            if (count < plain_text.size()) {
                matrix[row*num_of_columns+column] = plain_text[count]; // wee bit o' math, everything else pretty easy
            } else matrix[row*num_of_columns+column] = 'Z';
            count++;
        }
    }
    string cipher_text;
    for (int row = 0; row < num_of_rows; row++) {
        for (int column = 0; column < num_of_columns; column++) {
            cipher_text.append(1, matrix[row*num_of_columns+column]);
        }
    }

    return cipher_text;
}

// Interleave write by rows
string interleave_wbr(const string& plain_text, const int num_of_columns) {
    int num_of_rows = ceil(plain_text.size() / (double)num_of_columns); int count = 0;
    // Need to fill remainder of matrix with Z's
    auto *matrix = new char[num_of_columns*num_of_rows]; // large block of memory instead of dynamic # of column's
    for (int row = 0; row < num_of_rows; row++) {
        for (int column = 0; column < num_of_columns; column++) {
            if (count < plain_text.size()) {
                matrix[row*num_of_columns+column] = plain_text[count]; // wee bit o' math, everything else pretty easy
            } else matrix[row*num_of_columns+column] = 'Z';
            count++;
        }
    }

    string cipher_text;
    for (int column = 0; column < num_of_columns; column++) {
        for (int row = 0; row < num_of_rows; row++) {
            cipher_text.append(1, matrix[row*num_of_columns+column]);
        }
    }

    return cipher_text;
}

bool write_to_file(const string& filename, const string& cipher_text) {
    ofstream output (filename); // ios::out
    if (output.is_open()) {
        for (char i : cipher_text) {
            output << i;
        }
        output.close();
        return true;
    } else cout << "Something went wrong" << endl;
    return false;
}