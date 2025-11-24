/*
    THEORY:
    -------
    Subnetting allows a network to be divided into smaller subnetworks.
    It is used in IP addressing (IPv4) to increase efficiency and security.

    This simple program performs:
        • Conversion of IP address to its binary form
        • Conversion of subnet mask to CIDR notation (example: /24)
        • Calculation of number of hosts in the subnet

    IP Address:
    -----------
    Format: A.B.C.D  (each 0–255)
    Example: 192.168.1.10

    Subnet Mask:
    ------------
    A subnet mask has a certain number of 1s followed by 0s.
    Example: 255.255.255.0  →  11111111.11111111.11111111.00000000  →  /24

    Host Count Formula:
    -------------------
        hosts = 2^(32 - prefix_length) - 2
        (subtract 2 for network and broadcast addresses)
*/

#include <iostream>          // For input/output
using namespace std;         // Avoid writing std:: everywhere

// Function to convert a number (0–255) to 8-bit binary string
string toBinary(int num)
{
    string bin = "00000000";     // Start with 8 zeros
    for (int i = 7; i >= 0; i--) // Fill bits from right to left
    {
        if (num % 2 == 1)
            bin[i] = '1';        // Set bit if remainder is 1
        num /= 2;                // Divide by 2
    }
    return bin;
}

int main()
{
    int ip[4];                   // IP address octets
    int mask[4];                 // Subnet mask octets

    cout << "Enter IP Address (4 numbers, 0–255): ";
    cin >> ip[0] >> ip[1] >> ip[2] >> ip[3];

    cout << "Enter Subnet Mask (4 numbers, 0–255): ";
    cin >> mask[0] >> mask[1] >> mask[2] >> mask[3];

    // Convert each IP octet to binary
    cout << "\nBinary IP Address: ";
    for (int i = 0; i < 4; i++)
    {
        cout << toBinary(ip[i]);
        if (i < 3)
            cout << ".";
    }

    // Count how many 1s are in the subnet mask (CIDR prefix)
    int prefix = 0;
    for (int i = 0; i < 4; i++)
    {
        int value = mask[i];
        for (int bit = 7; bit >= 0; bit--)
        {
            if (value & (1 << bit)) // check if bit is 1
                prefix++;
        }
    }

    cout << "\nSubnet Mask Prefix: /" << prefix << endl;

    // Calculate number of hosts available
    int hostBits = 32 - prefix;       // Number of host bits
    int hosts = 1;                    // Hosts = 2^(hostBits) - 2

    for (int i = 0; i < hostBits; i++)
    {
        hosts = hosts * 2;            // Multiplying to get power of 2
    }

    hosts -= 2;                        // Subtract network & broadcast

    cout << "Available Hosts in Subnet: " << hosts << endl;

    return 0; // End program
}


/*
    ===================================
    SAMPLE INPUT / OUTPUT (AS COMMENTS)
    ===================================

    INPUT:
    Enter IP Address (4 numbers, 0–255): 192 168 1 10
    Enter Subnet Mask (4 numbers, 0–255): 255 255 255 0

    OUTPUT:
    Binary IP Address: 11000000.10101000.00000001.00001010
    Subnet Mask Prefix: /24
    Available Hosts in Subnet: 254
*/
