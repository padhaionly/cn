#include <iostream>

#include <string>

using namespace std;

// Function to perform XOR between two binary strings

string xorStrings(string a, string b) {

    string result = "";

    for (int i = 1; i < b.length(); i++) {

        result += (a[i] == b[i]) ? '0' : '1';

    }

    return result;

}

// Function to modulate (divide) the data using the key (generator polynomial)

string mod2div(string dividend, string divisor) {

    int pick = divisor.length();

    string tmp = dividend.substr(0, pick);

    while (pick < dividend.length()) {

        if (tmp[0] == '1') {

            tmp = xorStrings(divisor, tmp) + dividend[pick];

        } else {

            tmp = xorStrings(string(pick, '0'), tmp) + dividend[pick];

        }

        pick += 1;

    }

    // For the last n bits

    if (tmp[0] == '1') {

        tmp = xorStrings(divisor, tmp);

    } else {

        tmp = xorStrings(string(pick, '0'), tmp);

    }

    return tmp;

}

// Function to encode data using CRC

string encodeData(string data, string key) {

    int keyLen = key.length();

    string appendedData = data + string(keyLen - 1, '0');

    string remainder = mod2div(appendedData, key);

    string codeword = data + remainder;

    return codeword;

}

int main() {

    string data, key;

    cout << "Enter data: ";

    cin >> data;

    cout << "Enter generator polynomial (key): ";

    cin >> key;

    string codeword = encodeData(data, key);

    cout << "Encoded Data (Data + CRC): " << codeword << endl;


    string checkRemainder = mod2div(codeword, key);

    if (checkRemainder.find('1') != string::npos) {

        cout << "Error detected in received data!" << endl;

    } else {

        cout << "No error detected." << endl;

    }

    return 0;

}



