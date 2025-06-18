#include <reg52.h>

sbit r1 = P2^3;
sbit r2 = P2^4;
sbit r3 = P2^5;
sbit r4 = P2^6;
sbit c1 = P2^0;
sbit c2 = P2^1;
sbit c3 = P2^2;

unsigned char seg[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};

void delay(unsigned int a){
	unsigned int i,j;
	for(i=0;i<a;i++)
		for(j=0;j<100;j++);
}

void main(){
	P2 = 0xFF;  // Set all P1 pins high initially
	while(1){
		r1 = 0; r2 = r3 = r4 = 1;  // Activate row 1
		if(c1 == 0){ P1 = seg[1]; delay(50); }
		if(c2 == 0){ P1 = seg[2]; delay(50); }
		if(c3 == 0){ P1 = seg[3]; delay(50); }

		r2 = 0; r1 = r3 = r4 = 1;  // Activate row 2
		if(c1 == 0){ P1 = seg[4]; delay(50); }
		if(c2 == 0){ P1 = seg[5]; delay(50); }
		if(c3 == 0){ P1 = seg[6]; delay(50); }

		r3 = 0; r1 = r2 = r4 = 1;  // Activate row 3
		if(c1 == 0){ P1 = seg[7]; delay(50); }
		if(c2 == 0){ P1 = seg[8]; delay(50); }
		if(c3 == 0){ P1 = seg[9]; delay(50); }

		r4 = 0; r1 = r2 = r3 = 1;  // Activate row 4
		if(c2 == 0){ P1 = seg[0]; delay(50); }  // Example
	}
}
