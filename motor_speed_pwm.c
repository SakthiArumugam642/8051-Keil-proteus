#include <reg51.h>

sbit in1 = P3^0; // input 1
sbit en  = P1^7; // enable pin 

sbit s1 = P2^1; // 25% duty cycle
sbit s2 = P2^2; // 50% duty cycle
sbit s3 = P2^3; // 75% duty cycle
sbit s4 = P2^4; // 100% duty cycle

unsigned int mode = 0; // Stores selected duty cycle

void debounce_delay(){
	unsigned int i = 0;
	for(i = 0; i < 1275; i++);
}

void d_25_delay(){
	TR0 = 0;
	TF0 = 0;
	TH0 = 0xc0;
	TL0 = 0x00;
	TR0 = 1;
	while(TF0 == 0);
	TR0 = 0;
	TF0 = 0;
}

void d_50_delay(){
	TR0 = 0;
	TF0 = 0;
	TH0 = 0x80;
	TL0 = 0x00;
	TR0 = 1;
	while(TF0 == 0);
	TR0 = 0;
	TF0 = 0;
}

void d_75_delay(){
	TR0 = 0;
	TF0 = 0;
	TH0 = 0x40;
	TL0 = 0x00;
	TR0 = 1;
	while(TF0 == 0);
	TR0 = 0;
	TF0 = 0;
}

void d_100_delay(){
	TR0 = 0;
	TF0 = 0;
	TH0 = 0x00;
	TL0 = 0x00;
	TR0 = 1;
	while(TF0 == 0);
	TR0 = 0;
	TF0 = 0;
}

int main(){
	TMOD = 0x01;  // Timer0 Mode 1
	s1 = s2 = s3 = s4 = 1;  // Set as input with pull-up

	while(1){
		// Set mode once on button press
		if(s1 == 0){
			debounce_delay();
			if(s1 == 0) mode = 1;
		}
		else if(s2 == 0){
			debounce_delay();
			if(s2 == 0) mode = 2;
		}
		else if(s3 == 0){
			debounce_delay();
			if(s3 == 0) mode = 3;
		}
		else if(s4 == 0){
			debounce_delay();
			if(s4 == 0) mode = 4;
		}

		// PWM based on latched mode
		if(mode == 1){
			in1 = en = 1;
			d_25_delay();
			in1 = en = 0;
			d_75_delay();
		}
		else if(mode == 2){
			in1 = en = 1;
			d_50_delay();
			in1 = en = 0;
			d_50_delay();
		}
		else if(mode == 3){
			in1 = en = 1;
			d_75_delay();
			in1 = en = 0;
			d_25_delay();
		}
		else if(mode == 4){
			in1 = en = 1;
			d_100_delay();
		}
		else {
			in1 = en = 0; 
		}
	}
}
