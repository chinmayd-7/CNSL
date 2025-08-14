#include<iostream>
#include<string>
using namespace std;

// Converts 8-bit binary string to integer
int binaryToInt(const string& binary) {
    int result = 0;
    int length = binary.length();

    for (int i = 0; i < length; i++) {
        if (binary[i] == '1') {
            result += (1 << (length - 1 - i));
        } else if (binary[i] != '0') {
            cout << "Invalid binary digit: " << binary[i] << endl;
            return -1;
        }
    }
    return result;
}

// Calculates bits to borrow from host part
int bitsToBorrow(int requiredSubnets) {
    int bits = 0;
    while ((1 << bits) < requiredSubnets) {
        bits++;
    }
    return bits;
}

// Fills subnet mask in binary form
void fillSubnetMaskBits(int cidr, int borrowedBits, string subnetMask[4]) {
    int totalBits = cidr + borrowedBits;
    if (totalBits > 32) totalBits = 32;

    for (int i = 0; i < 4; i++) {
        string octetBits = "";
        for (int j = 0; j < 8; j++) {
            int bitIndex = i * 8 + j;
            octetBits += (bitIndex < totalBits) ? '1' : '0';
        }
        subnetMask[i] = octetBits;
    }
}

// Converts dotted IP string to 32-bit int
unsigned int ipToInt(const string& ip) {
    int a, b, c, d;
    sscanf(ip.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d);
    return (a << 24) | (b << 16) | (c << 8) | d;
}

// Converts 32-bit int to dotted IP string
string intToIP(unsigned int ip) {
    return to_string((ip >> 24) & 0xFF) + "." +
           to_string((ip >> 16) & 0xFF) + "." +
           to_string((ip >> 8) & 0xFF) + "." +
           to_string(ip & 0xFF);
}

int main() {
    int CIDR, subnetCnt;
    string IP;
    
    cout << "Enter IP address: ";
    cin >> IP;
    
    cout << "Enter number of network bits (CIDR): ";
    cin >> CIDR;
    
    cout << "Enter number of subnets to be formed: ";
    cin >> subnetCnt;

    int borrowed = bitsToBorrow(subnetCnt);
    string subnetMask[4];

    fillSubnetMaskBits(CIDR, borrowed, subnetMask);

    int totalNetworkBits = CIDR + borrowed;
    if (totalNetworkBits > 32) totalNetworkBits = 32;

    int hostBits = 32 - totalNetworkBits;
    int hostsPerSubnet = (hostBits > 0) ? ((1 << hostBits) ) : 0;
    int blockSize = (1 << hostBits);  // Total IPs per subnet (including net/broadcast)

    // Display subnet mask

    cout << "\nSubnet mask (decimal): ";
    for (int i = 0; i < 4; i++) {
        cout << binaryToInt(subnetMask[i]);
        if (i < 3) cout << ".";
    }

    cout << "\nUsable hosts per subnet: " << hostsPerSubnet << endl;

    // Calculate and display subnet ranges
    unsigned int baseIP = ipToInt(IP);
    int totalSubnets = (1 << borrowed);

    cout << "\nSubnet Table :\n";
	cout << "---------------------------------------------\n";
	cout << "Subnet\tStart IP\t\tEnd IP\n";
	cout << "---------------------------------------------\n";

	for (int i = 0; i < totalSubnets; i++) {
	    unsigned int network = baseIP + (i * blockSize);
	    unsigned int broadcast = network + blockSize - 1;

	    cout << i + 1 << "\t"
         << intToIP(network) << "\t"
         << intToIP(broadcast) << endl;
	}


    return 0;
}

