#include<reg52.h>

void delay(unsigned int n){
	unsigned int i,j;
	for(i=0;i<n;i++){
		for(j=i;j<n;j++);
	}
}

int main(){
	
	/*
	// for controlling motor on & off status and rotation direction status
	while(1){
	P3 = 0x01;
	delay(500);
	P3=0x02;
	delay(500);
	}
	*/
	
	// for controlling motor on or off status
	while(1){
		P2 =0x01;
	}
	
	
}