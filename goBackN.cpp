#include<iostream>
#include<vector>
using namespace std;

const int WINDOW_SIZE=3;
const int TOTAL_FRAMES = 6;

bool lost_once = false;

bool isLost(int frame) {
    if (frame == 1 && !lost_once) {
        lost_once = true;
        return true;  
    }
    return false;    
}

int main() {
    vector<bool> ack(TOTAL_FRAMES, false);

    int base = 0;         
    int nextSeqNum = 0;   

    while (base < TOTAL_FRAMES) {

        while (nextSeqNum < base + WINDOW_SIZE && nextSeqNum < TOTAL_FRAMES) {
            cout << "Sending frame " << nextSeqNum << endl;

            if (isLost(nextSeqNum)) {
                cout << "Frame " << nextSeqNum << " lost. Need to resend from frame " << base << endl;
                break;  
            } else {
                cout << "Frame " << nextSeqNum << " received, sending ACK" << endl;
                ack[nextSeqNum] = true;
                nextSeqNum++;
            }
        }

        while (base < TOTAL_FRAMES && ack[base]) {
            base++;
        }

        if (nextSeqNum > base + WINDOW_SIZE || (nextSeqNum < base + WINDOW_SIZE && lost_once && !ack[nextSeqNum - 1])) {
            cout << "\nTimeout or loss detected, resending from frame " << base << "\n\n";
            nextSeqNum = base;  // Go back and resend from base
        }

        cout << "\nSliding window base to " << base << "\n\n";
    }

    cout << "All frames sent and acknowledged successfully." << endl;

    return 0;
}
