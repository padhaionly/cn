/*
    THEORY:
    -------
    This program implements CRC (Cyclic Redundancy Check), which is a
    very common error-detection technique used in data communication.

    How CRC works:
    1. Sender chooses a GENERATOR POLYNOMIAL (example: 1101)
    2. Append (degree of generator - 1) zeros to the data.
    3. Perform BINARY DIVISION using XOR (no carry).
    4. The remainder becomes the CRC bits.
    5. Transmitted frame = original data + CRC remainder.

    On the RECEIVER SIDE:
    - Divide the received frame by the same generator.
    - If remainder = 0 → No error.
    - Otherwise → Error detected.

    NOTE:
    • CRC uses XOR instead of real subtraction.
    • CRC can detect burst errors more effectively than parity or checksum.
*/

#include <iostream>       // Required for input/output
using namespace std;      // To avoid writing std:: repeatedly

// Function to perform XOR between two bits ('0' or '1')
char XOR(char a, char b)
{
    if (a == b)           // If both bits are same → XOR = 0
        return '0';
    else                  // If bits differ → XOR = 1
        return '1';
}

int main()
{
    string data;          // Stores original data bits
    string generator;     // Stores generator polynomial bits
    string temp;          // Temporary string used for division
    string remainder;     // Stores the final CRC remainder

    cout << "Enter data bits (example: 1101011011): ";
    cin >> data;          // Read data input

    cout << "Enter generator polynomial (example: 1101): ";
    cin >> generator;     // Read generator polynomial

    int dataLength = data.length();          // Length of data bits
    int genLength = generator.length();      // Length of generator
    int zerosToAdd = genLength - 1;          // Number of zeros to append

    // Append zeros at the end of data (for CRC calculation)
    string appendedData = data;              // Start with original data
    for (int i = 0; i < zerosToAdd; i++)     // Add required number of zeros
    {
        appendedData += '0';                 // Append '0'
    }

    temp = appendedData;                     // Copy data+zeros into temp

    // Perform binary division using XOR method
    for (int i = 0; i <= dataLength - 1; i++)
    {
        if (temp[i] == '1')                  // Division only if leading bit is 1
        {
            for (int j = 0; j < genLength; j++)
            {
                // Replace bits with XOR of divisor and dividend
                temp[i + j] = XOR(temp[i + j], generator[j]);
            }
        }
        // If bit is '0', do nothing (skip – implicit division)
    }

    // Extract remainder (last genLength - 1 bits)
    remainder = temp.substr(dataLength, zerosToAdd);

    // Display the CRC remainder
    cout << "CRC Remainder: " << remainder << endl;

    // Final transmitted frame = original data + CRC remainder
    cout << "Transmitted Frame: " << data + remainder << endl;

    return 0;       // End of program
}
