#include <reg51.h>

sbit scl = P2^0;
sbit sda = P2^1;

void delay(unsigned int j){
	unsigned int i;
	for(i=0;i<j;i++);
	for(i=0;i<j;i++);
	
}

void i2c_start(){
	sda = 1;
	scl = 1;
	delay(5);
	sda = 0;
	delay(5);
	scl = 0;
}

void i2c_stop(){
	scl = 0;
	sda = 0;
	delay(5);
	scl = 1;
	delay(5);
	sda = 1;
}

void i2c_write(unsigned char dat){
    unsigned int i;
    
    for(i=0;i<8;i++){
        sda = (dat & 0x80) ? 1 : 0;  // send MSB
        scl = 1;
        delay(5);
        scl = 0;
        dat <<= 1;
    }

    sda = 1;  
    scl = 1;
    delay(5);
		while(sda==1);
    scl = 0;
    delay(5);
}


unsigned char i2c_read(){
		unsigned int i;
		bit bit_data;
		unsigned char dat = 0;
		for(i=0;i<8;i++){
			scl = 1;
			delay(5);
			bit_data = sda;
			dat = dat<<1;
			dat = dat|bit_data;
			scl = 0;
		}
		sda = 1;
		scl = 1;
		delay(5);
		scl = 0;
		return dat;
}

void main(){
	unsigned char x;
		i2c_start();
		i2c_write(0xA0);
		i2c_write(0x00);
		i2c_write('A');
		i2c_start();
		i2c_write(0xA1);
		x = i2c_read();
		i2c_stop();
	
	while(1);
}
