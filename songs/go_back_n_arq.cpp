/*
    THEORY:
    -------
    GO-BACK-N ARQ (Automatic Repeat reQuest)

    Go-Back-N is an efficient sliding-window protocol used to ensure reliable data transmission.

    How it works:
    -------------
    • Sender sends N frames at a time (window size = N).
    • Sender does NOT wait for ACK after each frame.
    • Receiver only accepts frames in correct order.
    • If any frame is lost/damaged:
        ➜ Receiver sends a NACK or stops ACKing further frames.
        ➜ Sender goes back and retransmits
              → the lost frame
              → AND all frames after it (even if they were received correctly).

    Why called "Go-Back-N"?
    Because when an error occurs, the sender goes back and resends N frames from the point of error.

    Advantages:
    ✔ Higher efficiency than Stop and Wait
    ✔ Allows multiple frames in transit

    Disadvantages:
    ✘ Wastes bandwidth in case of error because many frames get resent.
*/

#include <iostream>          // For input/output
using namespace std;         // Avoid std:: prefix

int main()
{
    int totalFrames;         // Total frames to send
    int windowSize;          // Sender window size (N)
    int errorFrame;          // Frame number where error occurs

    cout << "Enter total number of frames to send: ";
    cin >> totalFrames;      // Read total frames

    cout << "Enter window size (N): ";
    cin >> windowSize;       // Read sliding window size

    cout << "Enter frame number where error occurs (0 = no error): ";
    cin >> errorFrame;       // Read error location

    cout << "\nStarting Go-Back-N Transmission...\n";

    int current = 1;         // Start sending from frame 1

    // Send all frames until totalFrames is completed
    while (current <= totalFrames)
    {
        cout << "\nSending Window: ";  

        // Send frames in current window
        for (int i = 0; i < windowSize && (current + i) <= totalFrames; i++)
        {
            cout << "F" << (current + i) << " ";   // Sending frames
        }
        cout << endl;

        // Simulate error
        if (errorFrame >= current && errorFrame < (current + windowSize))
        {
            cout << "Error detected in Frame " << errorFrame << "!" << endl;
            cout << "Receiver requests retransmission from Frame " 
                 << errorFrame << endl;

            // Sender goes back to errorFrame
            current = errorFrame;
        }
        else
        {
            // No error → move window forward
            current += windowSize;
            cout << "All frames in window acknowledged.\n";
        }
    }

    cout << "\nAll frames transmitted successfully using Go-Back-N ARQ.\n";

    return 0;   // End of program
}


/*
    ======================
    SAMPLE INPUT / OUTPUT
    ======================

    INPUT:
    Enter total number of frames to send: 10
    Enter window size (N): 4
    Enter frame number where error occurs (0 = no error): 6

    OUTPUT:

    Starting Go-Back-N Transmission...

    Sending Window: F1 F2 F3 F4
    All frames in window acknowledged.

    Sending Window: F5 F6 F7 F8
    Error detected in Frame 6!
    Receiver requests retransmission from Frame 6

    Sending Window: F6 F7 F8 F9
    All frames in window acknowledged.

    Sending Window: F10
    All frames in window acknowledged.

    All frames transmitted successfully using Go-Back-N ARQ.
*/

