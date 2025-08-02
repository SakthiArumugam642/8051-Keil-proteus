#include <reg51.h>
#include <stdio.h>

sbit rs = P3^0;    
sbit rw = P3^1;     
sbit en = P3^3;     

volatile unsigned int count =0;
unsigned char buffer[5];

void delay(unsigned int i){
	int j,k;
	for(j=0;j<1275;j++){
		for(k=0;k<=i;k++);
	}
}

void lcd_cmd(unsigned char ch){
	P2 = ch;
	rs = 0;
	rw=0;
	en = 1;
	delay(20);
	en=0;
}

void lcd_init(){
	lcd_cmd(0x38);
	lcd_cmd(0x0c);
	lcd_cmd(0x01);
	lcd_cmd(0x80);

}

void lcd_char(unsigned char ch){
	P2 = ch;
	rs = 1;
	rw=0;
	en = 1;
	delay(20);
	en=0;
}

void lcd_str(unsigned char * str){

	while(*str){
		lcd_char(*str);
		str +=1;
	}
}

void Ext0_ISR(void) interrupt 0{
	count++;
	//delay(20);
}

int main(){
	
	lcd_init();
	EA = 1;
	EX0 = 1;
	IT0 = 1;
	
	
	while(1){
		lcd_cmd(0x0c);
		lcd_cmd(0x01);
		sprintf(buffer,"%d",count);
		lcd_str(buffer);
	}
	
	


}