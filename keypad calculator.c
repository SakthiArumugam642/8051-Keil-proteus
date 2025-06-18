#include <reg52.h>
#include <stdio.h>

sbit r1 = P2^0;
sbit r2 = P2^1;
sbit r3 = P2^2;
sbit r4 = P2^3;
sbit c1 = P2^4;
sbit c2 = P2^5;
sbit c3 = P2^6;
sbit c4 = P2^7;

sbit rs = P3^7;
sbit rw = P3^6;
sbit en = P3^5;

int op,oper_sts=0,num1=0,num2=0,res=0;
char key;

unsigned char keypad[4][4] = {
		{'7','8','9','/'},
    {'4','5','6','*'},
    {'1','2','3','-'},
    {'C','0','=','+'}
};

void delay(unsigned int a){
	unsigned int i,j;
	for(i=0;i<a;i++){
		for(j=0;j<100;j++);
}
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

char getkey(){
	while(1){
		r1 = 0; r2 = r3 = r4 = 1;  // Activate row 1
		if(c1 == 0){ delay(50);while(c1==0); return keypad[0][0]; }
		if(c2 == 0){ delay(50);while(c2==0); return keypad[0][1]; }
		if(c3 == 0){ delay(50);while(c3==0); return keypad[0][2]; }
		if(c4 == 0){ delay(50);while(c4==0); return keypad[0][3]; }
		
		r2 = 0; r1 = r3 = r4 = 1;  // Activate row 2
		if(c1 == 0){ delay(50);while(c1==0); return keypad[1][0]; }
		if(c2 == 0){ delay(50);while(c2==0); return keypad[1][1]; }
		if(c3 == 0){ delay(50);while(c3==0); return keypad[1][2]; }
		if(c4 == 0){ delay(50);while(c4==0); return keypad[1][3]; }

		r3 = 0; r1 = r2 = r4 = 1;  // Activate row 3
		if(c1 == 0){ delay(50);while(c1==0); return keypad[2][0]; }
		if(c2 == 0){ delay(50);while(c2==0); return keypad[2][1]; }
		if(c3 == 0){ delay(50);while(c3==0); return keypad[2][2]; }
		if(c4 == 0){ delay(50);while(c4==0); return keypad[2][3]; }

		r4 = 0; r1 = r2 = r3 = 1;  // Activate row 4
		if(c1 == 0){ delay(50);while(c1==0); return keypad[3][0]; }
		if(c2 == 0){ delay(50);while(c2==0); return keypad[3][1]; }
		if(c3 == 0){ delay(50);while(c3==0); return keypad[3][2]; }
		if(c4 == 0){ delay(50);while(c4==0); return keypad[3][3]; }
	}
}

void main(){
	char buf[20];
	lcd_init();
	lcd_string("Calc is ready!!!");
	delay(70);
	lcd_cmd(0x01);
 
	while(1){
		key = getkey();
		lcd_data(key);
		
		if(key>='0' && key <='9'){
			if(oper_sts ==0){
					num1 = num1*10 +(key-'0');
			}else num2 = num2*10 +(key-'0');
		}
		else if(key == '+' || key == '-' || key == '*' || key == '/'){
				oper_sts = 1;
				op = key;
		}
		else if(key == '='){
			switch(op){
				case '+':
					res = num1 + num2;
					break;
				case '-':
					res = num1 - num2;
					break;
				case '*':
					res = num1 * num2;
					break;
				case '/':
					res = num2!=0 ? num1/num2 : 0;
					break;
				default:
					res =0;
					break;
			}
			
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			
			sprintf(buf,"Ans: %d",(int)res);
			lcd_string(buf);
			delay(2000);
			
			lcd_cmd(0x01);
			oper_sts = op= num1=num2=res=0;
			
		}
		else if(key == 'C'){
				lcd_cmd(0x01);
			oper_sts = op= num1=num2=res=0;
		}
  }
}