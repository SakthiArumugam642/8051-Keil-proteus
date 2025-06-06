#include <reg52.h>

void delay(unsigned int n){
	int i,j;
	for(i=0;i<1000;i++){
	for(j = 0;j<n;j++);
	}
}

int main(){
	
	int arr[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};
	int k1,k2;
	while(1){
		int n=0;
		 while(n<=99){
						k1 = n/10;
						k2 = n%10;
					P2 = arr[k2];
					P0 = arr[k1];
					delay(35);
					n++;
		      }
		}
}