/*
    THEORY:
    -------
    This program implements a simple PARITY CHECK mechanism.
    Parity is used in data communication to detect single-bit errors.
    There are two types of parity:
      1. Even Parity  → Number of 1's in data (including parity bit) must be EVEN
      2. Odd Parity   → Number of 1's in data (including parity bit) must be ODD

    How it works:
    - The user enters a binary data string (example: 1010110)
    - The program counts the number of 1's
    - Based on the chosen parity (even or odd), the program adds a parity bit:
          EVEN parity: If count of 1s is odd → parity bit = 1
                       If count is even → parity bit = 0
          ODD parity:  If count of 1s is odd → parity bit = 0
                       If count is even → parity bit = 1
    - The program prints the transmitted data with the parity bit.
*/

#include <iostream>      // Required for input and output
using namespace std;     // To avoid writing std:: everywhere

int main()               // main function starts here
{
    string data;         // variable to store the input bit string
    int choice;          // variable for the user to choose even/odd parity
    int count = 0;       // variable to count number of 1's in the data

    cout << "Enter binary data (example: 1010110): ";  // ask user for input
    cin >> data;                                       // read the data string

    // Counting the number of 1's in the input
    for (int i = 0; i < data.length(); i++)            // loop through each bit
    {
        if (data[i] == '1')                            // check if character is '1'
        {
            count++;                                   // increase count of 1's
        }
    }

    cout << "Choose Parity Type:\n";                   // ask user to choose parity
    cout << "1. Even Parity\n";                        // option 1
    cout << "2. Odd Parity\n";                         // option 2
    cout << "Enter choice (1 or 2): ";                 // ask user for input
    cin >> choice;                                     // read user's choice

    int parityBit = 0;                                 // variable to store parity bit (0 or 1)

    // Logic for EVEN parity
    if (choice == 1)                                   // if user chooses EVEN
    {
        if (count % 2 != 0)                            // if number of 1's is ODD
        {
            parityBit = 1;                             // add 1 to make total EVEN
        }
        else                                           // if already even
        {
            parityBit = 0;                             // no change needed
        }

        cout << "Using EVEN Parity\n";                // display selected parity
    }
    // Logic for ODD parity
    else if (choice == 2)                              // if user chooses ODD
    {
        if (count % 2 == 0)                            // if number of 1's is EVEN
        {
            parityBit = 1;                             // add 1 to make total ODD
        }
        else                                           // if already odd
        {
            parityBit = 0;                             // no change needed
        }

        cout << "Using ODD Parity\n";                  // display selected parity
    }
    else                                               // if user enters invalid choice
    {
        cout << "Invalid choice! Program exiting.\n";  // show error
        return 0;                                      // exit program
    }

    // Display the final transmitted data
    cout << "Transmitted Data with Parity Bit: ";      // message
    cout << data << parityBit << endl;                 // append parity bit and print

    return 0;                                          // end of program
}
