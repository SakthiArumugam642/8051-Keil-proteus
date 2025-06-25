#include<reg52.h>

sbit in1 = P3^0;
sbit in2 = P3^1;
sbit en  = P3^2;

void delay(unsigned int n){
	unsigned int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<1275;j++);
	}
}

void pwm_generate(){
en = 1;
	delay(5);
	en = 0;
	delay(15);
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
	
	/*// for controlling motor on or off status
	while(1){
		P2 =0x01;
	}*/
	
	// pwm generation using function delay
	in1 = 1;
	in2 = 0;
	
	while(1){
	pwm_generate();
	}
	
	
	
	
}