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

    cout << "\n--- Selective Repeat ARQ ---\n";
    cout << "Sender\t\tReceiver\n";

    vector<bool> ack(n, false); // track ACKs
    int i = 0;

    while (i < n) {
        int windowEnd = min(i + windowSize, n);

        cout << "\nSending Window: ";
        for (int j = i; j < windowEnd; j++)
            if (!ack[j]) cout << frames[j] << " ";
        cout << endl;

        for (int j = i; j < windowEnd; j++) {
            if (!ack[j]) {
                bool error = rand() % 2;
                if (!error) {
                    cout << "Frame " << frames[j] << " received successfully.\n";
                    cout << "ACK sent for Frame " << frames[j] << endl;
                    ack[j] = true;
                } else {
                    cout << "!! Frame " << frames[j] << " lost -> Will resend later\n";
                }
            }
        }

        // Slide window forward only if leftmost acknowledged
        while (i < n && ack[i]) i++;
    }

    cout << "\nAll frames sent and acknowledged successfully.\n";
    return 0;
}
