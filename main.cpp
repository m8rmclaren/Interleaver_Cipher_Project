#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string read_from_file(const string& filename);
string interleave(const string& plain_text, int num_of_columns);
bool write_to_file(const string& filename, const string& cipher_text);

int main() {
    string plaintext = read_from_file("/Users/haydenroszell/Documents/School/College/ERAU/Sophomore/sem2/CS303/projects/project1/input.txt");
    cout << plaintext << endl << "Enter # of columns for interleaver: ";
    int num_of_columns; cin >> num_of_columns;
    string cipher_text = interleave(plaintext, num_of_columns);
    if (write_to_file("/Users/haydenroszell/Documents/School/College/ERAU/Sophomore/sem2/CS303/projects/project1/output.txt", cipher_text))
        cout << "Write succeeded" << endl;
    else cout << "Write failed" << endl;

    return 0;
}

string read_from_file(const string& filename) {
    fstream input (filename);
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
        if (ispunct(data[i]) || data[i] == ' ') {
            data.erase(i--, 1);
            length = data.size();
        }
        data[i] = toupper(data[i]);
    }
    return data;
}

string interleave(const string& plain_text, const int num_of_columns) {
    int num_of_rows = ceil(plain_text.size() / (double)num_of_columns);

    int count = 0;

    auto *matrix = new char[num_of_columns*num_of_rows]; // large block of memory instead of dynamic # of column's
    for (int column = 0; column < num_of_columns; column++) {
        for (int row = 0; row < num_of_rows; row++) {
            if (count < plain_text.size()) {
                matrix[row*num_of_columns+column] = plain_text[count]; // wee bit o' number theory
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

bool write_to_file(const string& filename, const string& cipher_text) {
    ofstream output (filename);
    if (output.is_open()) {
        for (int i = 0; i < cipher_text.size(); i++) {
            output << cipher_text[i];
        }
        output.close();
        return true;
    } else cout << "Something went wrong" << endl;
    return false;
}