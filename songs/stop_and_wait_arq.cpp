/*
    THEORY:
    -------
    STOP AND WAIT ARQ (Automatic Repeat reQuest)

    This is one of the simplest error-control protocols used in data communication.
    It ensures reliable transmission between sender and receiver.

    How it works:
    -------------
    1. Sender sends one frame at a time.
    2. Sender waits for an ACK (Acknowledgment) for that frame.
    3. If ACK is received → Sender sends next frame.
    4. If ACK is lost or delayed → Sender retransmits the same frame.
    5. This continues until all frames are successfully sent.

    Key Features:
    - Simple and reliable
    - Low efficiency because only one frame is sent at a time
*/

#include <iostream>      // For input/output
using namespace std;     // To avoid writing std:: everywhere

int main()
{
    int totalFrames;     // Total number of frames to send
    int ack;             // Variable to simulate ACK behavior

    cout << "Enter total number of frames to send: ";
    cin >> totalFrames;  // User enters frame count

    // Loop through each frame one-by-one
    for (int i = 1; i <= totalFrames; i++)
    {
        cout << "\nSending Frame " << i << "..." << endl;  // Sender sends frame i
        cout << "Enter ACK for frame " << i << " (1 = Received, 0 = Lost): ";
        cin >> ack;          // User simulates ACK received or lost

        // If ACK received
        if (ack == 1)
        {
            cout << "ACK received for Frame " << i << endl; // Receiver acknowledged
        }
        else
        {
            // If ACK lost or not received
            cout << "ACK lost! Retransmitting Frame " << i << "..." << endl;
            cout << "ACK received for Frame " << i << " on retransmission." << endl;
        }
    }

    cout << "\nAll frames transmitted successfully.\n"; // All done

    return 0;  // End of program
}


/*
    ======================
    SAMPLE INPUT / OUTPUT
    ======================

    INPUT:
    Enter total number of frames to send: 4

    Sending Frame 1...
    Enter ACK for frame 1 (1 = Received, 0 = Lost): 1
    ACK received for Frame 1

    Sending Frame 2...
    Enter ACK for frame 2 (1 = Received, 0 = Lost): 0
    ACK lost! Retransmitting Frame 2...
    ACK received for Frame 2 on retransmission.

    Sending Frame 3...
    Enter ACK for frame 3 (1 = Received, 0 = Lost): 1
    ACK received for Frame 3

    Sending Frame 4...
    Enter ACK for frame 4 (1 = Received, 0 = Lost): 1
    ACK received for Frame 4

    OUTPUT:
    All frames transmitted successfully.
*/
