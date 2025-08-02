#include <reg51.h>

sbit led = P2^2;

volatile unsigned int count1=0;  // since this var is changed inside ISR
unsigned int count2=0;

void Timer0_ISR(void) interrupt 1 {
	count1++;
	TF0 = 0;
	TH0 = 0x4B;
	TL0 = 0xFD;
}

void Ext0_ISR(void) interrupt 0{
	
	led = 0;
	TMOD |= 0x10;
	TR1 = 1;
	count2 = 0;
	while(count2<=100){ // 50 ms * 100 = 5secs
	TH1 = 0x4B;
	TL1 = 0xFD;
	while(TF1==0);
			count2++;
			TF1=0;
	}
}

int main(){
	
	led = 0;
	TMOD = 0x01;
	TF0 = 0;
	TH0 = 0x4B;
	TL0 = 0xFD;
	TR0 = 1;  
	
	EA = 1; // global interrupt enable
	ET0 = 1; // timer 0 interrupt
	EX0 = 1; // external interrupt 0
	IT0 = 1; // edge triggered
	
	PT0 = 0; // low priority
	PX0 = 1; // high priority
	
	while(1){
		
	if(count1>=20){ // 20 x 50 ms = 1s
		count1 = 0;
		led = ~led;
	}
}
}