/*
    THEORY:
    -------
    This program implements HAMMING CODE (Error Detection + Error Correction).

    Hamming Code allows us to:
    - Detect 1-bit errors
    - Correct 1-bit errors

    How Hamming Code Works:
    -----------------------
    1. The user enters data bits (example: 1011)
    2. We calculate the number of parity bits required (p),
       using the condition:
           2^p >= (data_bits + p + 1)
    3. Parity bits are placed at positions:
           1, 2, 4, 8, 16 ... (power of 2)
    4. Remaining positions are filled with data bits.
    5. Parity bits are calculated using EVEN PARITY.
    6. Final Hamming Code is printed.

    Example:
    Data = 1011
    Positions:
        p1 p2 d3 p4 d5 d6 d7
        Parity bits at 1,2,4
        Data bits at 3,5,6,7
*/

#include <iostream>      // Input/output library
using namespace std;     // Use standard namespace

int main()
{
    string data;         // To store the input data bits
    cout << "Enter data bits (example: 1011): ";
    cin >> data;         // Read user input

    int dataLen = data.length();       // Length of input data
    int p = 0;                         // Number of parity bits needed

    // Finding number of parity bits needed using: 2^p >= dataLen + p + 1
    while ((1 << p) < (dataLen + p + 1))  // (1<<p) means 2^p
    {
        p++;                               // Increase count until satisfied
    }

    int totalBits = dataLen + p;           // Total length of Hamming code
    char hamming[50];                      // Array to store Hamming bits

    // Initialize all bits to '0'
    for (int i = 1; i <= totalBits; i++)
    {
        hamming[i] = '0';
    }

    // Placing data bits into non-power-of-two positions
    int j = 0;                             // Index for input data
    for (int i = 1; i <= totalBits; i++)
    {
        // Check if 'i' is NOT power of 2 → place data bit
        if ((i & (i - 1)) != 0)            // property of power of 2
        {
            hamming[i] = data[j];          // Place data bit
            j++;                            // Move to next data bit
        }
    }

    // Calculate parity bits (Even Parity)
    for (int i = 0; i < p; i++)
    {
        int pos = (1 << i);                // Parity bit position
        int count = 0;                     // Count number of 1's covered

        // Check all bits influenced by this parity bit
        for (int k = pos; k <= totalBits; k += (pos * 2))
        {
            for (int x = k; x < (k + pos) && x <= totalBits; x++)
            {
                if (hamming[x] == '1')     // Count number of 1s
                {
                    count++;
                }
            }
        }

        // Set parity bit using EVEN parity rule
        if (count % 2 == 0)
        {
            hamming[pos] = '0';            // Even → parity = 0
        }
        else
        {
            hamming[pos] = '1';            // Odd → parity = 1
        }
    }

    // Printing final Hamming code
    cout << "\nGenerated Hamming Code: ";
    for (int i = 1; i <= totalBits; i++)
    {
        cout << hamming[i];               // Print each bit
    }
    cout << endl;                         // New line

    return 0;                             // End program
}
