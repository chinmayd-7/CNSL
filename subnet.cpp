#include<iostream>
using namespace std;
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
	
int bitsToBorrow(int requiredSubnets) {
    	int bits = 0;
    	while ((1 << bits) < requiredSubnets) {
        	bits++;
    	}
    	return bits;
}

void fillSubnetMaskBits(int cidr, int borrowedBits, string subnetMask[4]) {
    int totalBits = cidr + borrowedBits; 
    if (totalBits > 32) totalBits = 32;  

    for (int i = 0; i < 4; i++) {
        string octetBits = "";
        for (int j = 0; j < 8; j++) {
            int bitIndex = i * 8 + j;
            if (bitIndex < totalBits) {
                octetBits += '1';
            } else {
                octetBits += '0';
            }
        }
        subnetMask[i] = octetBits;
    }
}

int main(){
	int CIDR,subnetCnt;
	string IP;
	cout<<"Enter IP address :";
	cin>>IP;
	cout<<"Enter no. of network bits : ";
	cin>>CIDR;
	cout<<"Enter no. of subnets to be formed : ";
	cin>>subnetCnt;
	
	int bitsToBorrow=bitsToBorrow(subnetCnt);
	string subnetMask[4];
	
	fillSubnetMaskBits(CIDR,bitsToBorrow,subnetMask);
	
	int totalNetworkBits = CIDR + bitsToBorrow;
	if (totalNetworkBits > 32) totalNetworkBits = 32;

	int hostBits = 32 - totalNetworkBits;
	int hostsPerSubnet = (hostBits > 0) ? ( (1 << hostBits) - 2 ) : 0;
	
	cout << "Subnet mask : ";
	for (int i = 0; i < 4; i++) {
   		cout << binaryToInt(subnetMask[i]);
    		if (i < 3) cout << ".";
	}
	cout << endl;
	
	
}




	
