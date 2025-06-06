#include <reg52.h>
sbit sw = P1^1;


void delay(unsigned int n){
	int i,j;
	for(i=0;i<1000;i++){
	for(j = 0;j<n;j++);
	}
}

int main(){
	
	int arr[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};
	int n=0;
	int flag=0;
	P2 = arr[n];
	while(1){
		if(flag){
					
					n++;
					if(n>9) n=0;
					P2 = arr[n];
					delay(30);
		}
	if(sw == 0){
		delay(5);
		if(sw ==0){
		while(sw ==0);
		flag = ~flag;
	}
}
}
}