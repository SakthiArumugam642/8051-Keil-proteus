#include<reg51.h>

sbit relay = P2^0;

void delay(unsigned int n){
		unsigned int i,j;
	for(i = 0;i<n;i++){
		for(j =0;j<1275;j++);
	}

}

int main(){
	while(1){
		relay = 1;
		delay(100);
		relay =0;
		delay(100);
	}

}