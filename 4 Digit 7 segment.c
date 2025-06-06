#include <reg52.h>
sbit sw = P1^1;
sbit d1 = P1^4;
sbit d2 = P1^5;
sbit d3 = P1^6;
sbit d4 = P1^7;
unsigned int v0=0,v1=0,v2=0,v3=0,v4=0; 

void delay(unsigned int n){
	int i,j;
	for(i=0;i<1;i++){
	for(j = 0;j<n;j++);
	}
}

int main(){
	
	int arr[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};
	int n=0;
	
	while(1){
						
					v0++;
					if(v0 == 1){
						v0 = 0;
						v1++;
					}
					
					if(v1==10){
						v1 = 0;
						v2++;
					}
					P3 = 0xFF;
					d1=1;
					d2=d3=d4=0;
					P3 = arr[v1];
					delay(5);
					
					if(v2 == 10){
						v2 = 0;
						v3++;
					}
					P3 = 0xFF;
					d2=1;
					d1=d3=d4=0;
					P3 = arr[v2];
					delay(5);
					
					if(v3 == 10){
						v3 = 0;
						v4++;
					}
					P3 = 0xFF;
					d3=1;
					d1=d2=d4=0;
					P3 = arr[v3];
					delay(5);
					
					if(v4 == 10){
						v1=v2=v3=v4 = 0;
					break;
					}
					P3 = 0xFF;
					d4=1;
					d2=d3=d1=0;
					P3 = arr[v4];
					delay(5);
}
	while(1){
		
		P3=0xff;
		d1=1;
		d2=d3=d4=0;
		P3 = arr[0];
		delay(5)
		
		P3=0xff;
		d2=1;
		d1=d3=d4=0;
		P3 = arr[0];
		delay(5);

		P3=0xff;
		d3=1;
		d1=d2=d4=0;
		P3 = arr[0];
		delay(5);
		
		P3=0xff;
		d4=1;
		d1=d3=d2=0;
		P3 = arr[0];
		delay(5);
	}
}