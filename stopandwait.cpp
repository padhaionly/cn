#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));  // seed random generator

    int n;
    cout << "Total number of frames to send: ";
    cin >> n;

    int frames[n];
    cout << "Enter the frame numbers (or values): ";
    for (int i = 0; i < n; i++)
        cin >> frames[i];

    cout << "\nSender\t\t\t\tReceiver\n";

    int i = 0;
    while (i < n) {
        cout << "Sending Frame: " << frames[i] << "\t";

        bool ackLost = rand() % 2 == 0;

        cout << "Received Frame: " << frames[i] << endl;

        if (!ackLost) {
            cout << "Acknowledgement: " << frames[i] << endl;
            i++; 
        } else {
            cout << "!! ACK lost for Frame: " << frames[i] << " -> Resending...\n";
        }
    }

    cout << "\nAll frames sent and acknowledged successfully.\n";
    return 0;
}
