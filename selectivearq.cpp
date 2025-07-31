#include<iostream>
#include<vector>
using namespace std;

const int WINDOW_SIZE=3;
const int TOTAL_FRAMES = 6;

bool lost_once = false;

bool isLost(int frame) {
    if (frame == 1 && !lost_once) {
        lost_once = true;
        return true;  // Lost first time only
    }
    return false;     // Next attempts succeed
}

int main(){
	vector<bool> ack(TOTAL_FRAMES,false);
	
	int base=0;
	while(base< TOTAL_FRAMES){
		for(int i=0;i < base+WINDOW_SIZE && i<TOTAL_FRAMES;i++){
			if(!ack[i]){
				cout<<"Sending frame "<<i<<endl;
				if(isLost(i)){
					cout<<"Frame "<<i<<" Lost , Send again"<<endl;
				}else{
					cout<<"Frame received, sending acknowledgement"<<endl;
					ack[i]=true;
				}
			}
		}
		
		while(base<TOTAL_FRAMES && ack[base]){
			base++;
		}
		
		cout<<"\nSliding window base to "<<base<<"\n\n\n";
	}
	return 0;
}
