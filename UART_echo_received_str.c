#include <reg51.h>

void uart_init(){
	TMOD = 0x20;
	TH1 = 0xFD;
	SCON = 0x50;
	TR1 = 1;
}

void send_char(unsigned char ch){
	SBUF = ch;
	while(TI==0);
	TI=0;
}

void send_str(char * ch){
	while(*ch){
		send_char(*ch);
		ch++;
	}	
}

unsigned char char_receive(){
		while(RI==0);
		RI = 0;
		send_char(SBUF);
	return SBUF;
}

void str_receive(char * buffer){
		char ch;
	unsigned int i=0;
	while(1){
		ch = char_receive();
		if(ch == '\r'){
			buffer[i] = 0;
			break;
		}
		buffer[i++] = ch;
	}
}

int main(){
	
	char buffer[20];
	
	uart_init();
	send_str("Pls enter an integer\r\n");
	str_receive(buffer);

	
	send_str("You have entered\r\n");
	send_str(buffer);
	send_str("\r\n");
	
	send_str("Pls enter an float\r\n");
	str_receive(buffer);
	
	
	send_str("You have entered\r\n");
	send_str(buffer);
	send_str("\r\n");
	
	
	while(1);
}