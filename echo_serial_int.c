#include <reg51.h>

unsigned char ch;

void serial_init(){
	TMOD = 0x20;
	SCON = 0x50;
	TH1 = 0xFD;
	TR1 = 1;
}

void tx_char(unsigned char c){
	SBUF = c;
}

void Serial_ISR(void) interrupt 4{
	if(TI == 1){
		TI = 0;
	}
	if(RI == 1){
		ch = SBUF;
		tx_char(ch);
		RI = 0;
	}
}

int main(){
	serial_init();
	ES = EA = 1;
	while(1){
	}
}