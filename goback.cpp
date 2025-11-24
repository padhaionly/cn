#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

int main() {
    srand(time(0));

    int n, windowSize;
    cout << "Total number of frames to send: ";
    cin >> n;

    vector<int> frames(n);
    cout << "Enter the frame numbers: ";
    for (int i = 0; i < n; i++)
        cin >> frames[i];

    cout << "Enter the window size: ";
    cin >> windowSize;

    cout << "\n--- Go Back N ARQ ---\n";
    cout << "Sender\t\tReceiver\n";

    int i = 0;
    while (i < n) {
        int windowEnd = min(i + windowSize, n);
        cout << "\nSending Window: ";
        for (int j = i; j < windowEnd; j++)
            cout << frames[j] << " ";
        cout << endl;

        // Random error simulation
        bool errorHappened = rand() % 2;
        if (errorHappened) {
            int errorFrame = rand() % (windowEnd - i) + i;
            cout << "Received frames till " << frames[errorFrame] << " -> ERROR detected!\n";
            cout << "ACK sent only till Frame " << (errorFrame > i ? frames[errorFrame - 1] : -1) << endl;
            i = errorFrame; // go back to error frame
        } else {
            for (int j = i; j < windowEnd; j++) {
                cout << "Frame " << frames[j] << " received successfully.\n";
                cout << "ACK sent for Frame " << frames[j] << endl;
            }
            i = windowEnd; // slide window forward
        }
    }

    cout << "\nAll frames sent and acknowledged successfully.\n";
    return 0;
}
