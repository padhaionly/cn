/*
    THEORY:
    -------
    SELECTIVE REPEAT ARQ (Automatic Repeat reQuest)

    Selective Repeat ARQ is the most efficient sliding-window protocol.
    It improves over Go-Back-N by retransmitting ONLY the frame that had an error.

    How it works:
    -------------
    • Sender sends multiple frames (window size N)
    • Receiver individually ACKs each correct frame
    • If one frame is lost or corrupted:
          → Receiver sends a NACK (or simply does not ACK it)
          → Sender retransmits ONLY the problematic frame

    Advantages:
    ✔ Most efficient ARQ protocol
    ✔ Only erroneous frames are resent
    ✔ Useful for unreliable channels

    Disadvantages:
    ✘ Complex logic on both sender and receiver
*/

#include <iostream>       // For input/output
using namespace std;      // Use standard namespace

int main()
{
    int totalFrames;      // Total number of frames to send
    int windowSize;       // Window size used in Selective Repeat
    int errorFrame;       // Frame number where error occurs

    cout << "Enter total number of frames to send: ";
    cin >> totalFrames;   // Read total number of frames

    cout << "Enter window size (N): ";
    cin >> windowSize;    // Read sliding window size

    cout << "Enter frame number where error occurs (0 = no error): ";
    cin >> errorFrame;    // Read the frame at which error happens

    cout << "\nStarting Selective Repeat ARQ Transmission...\n";

    int current = 1;      // Current frame index

    // Send all frames one by one in window style
    while (current <= totalFrames)
    {
        cout << "\nSending Window: ";
        
        // Display frames being sent in current window
        for (int i = 0; i < windowSize && (current + i) <= totalFrames; i++)
        {
            cout << "F" << (current + i) << " ";
        }
        cout << endl;

        // Check if error is inside current window
        if (errorFrame >= current && errorFrame < (current + windowSize))
        {
            cout << "Error detected in Frame " << errorFrame << "!" << endl;
            cout << "Retransmitting ONLY Frame " << errorFrame << "..." << endl;
            cout << "Frame " << errorFrame << " received successfully.\n";

            // Move window ahead AFTER fixing error
            current += windowSize;
        }
        else
        {
            // No error → window moves ahead normally
            cout << "All frames in window acknowledged.\n";
            current += windowSize;
        }
    }

    cout << "\nAll frames transmitted successfully using Selective Repeat ARQ.\n";

    return 0;   // End of program
}


/*
    ===================================
    SAMPLE INPUT / OUTPUT (AS COMMENTS)
    ===================================

    INPUT:
    Enter total number of frames to send: 10
    Enter window size (N): 4
    Enter frame number where error occurs (0 = no error): 7


    OUTPUT:

    Starting Selective Repeat ARQ Transmission...

    Sending Window: F1 F2 F3 F4
    All frames in window acknowledged.

    Sending Window: F5 F6 F7 F8
    Error detected in Frame 7!
    Retransmitting ONLY Frame 7...
    Frame 7 received successfully.

    Sending Window: F9 F10
    All frames in window acknowledged.

    All frames transmitted successfully using Selective Repeat ARQ.
*/
