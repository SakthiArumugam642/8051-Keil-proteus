#include <reg52.h>

sbit rs = P3^7;
sbit rw = P3^6;
sbit en = P3^5;

void delay(unsigned int a){
	unsigned int i,j;
	for(i=0;i<a;i++)
		for(j=0;j<100;j++);
}

void lcd_cmd(unsigned char ch){
	P1 = ch;
	rs = 0;
	rw=0;
	en=1;
	delay(20);
	en=0;
}

void lcd_data(unsigned char ch){
	P1 = ch;
	rs = 1;
	rw=0;
	en=1;
	delay(20);
	en=0;
	
}

void lcd_string(char* str){
	int k=0;
	while(str[k]!='\0'){
	    lcd_data(str[k]);
			k++;
	}
}

void lcd_init(){
		lcd_cmd(0x38);
		lcd_cmd(0x0c);
		lcd_cmd(0x01);
	  lcd_cmd(0x80);
}

void main(){
	  int i;
	lcd_init();
	lcd_string("I Love U ManiMegalai");

	while(1){
		for(i=0; i<20; i++){
			delay(300);
			lcd_cmd(0x18);   // Shift entire display left
		}
	}
}