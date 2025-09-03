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
bit i2c_write(unsigned char c){
	unsigned char i = 0;
	bit ack;
	for(i = 0 ;i<8;i++){
		sda = (c&0x80) ? 1 : 0;
		scl = 1;
		delay(5);
		scl = 0;
		c = c<<1;
	}
		sda = 1;  
    scl = 1;
    delay(5);
		ack = (sda==0)?1:0;
    scl = 0;
    delay(5);
		return ack;
}
unsigned char i2c_read(bit ack){
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
		sda = (ack) ? 0 : 1;
		scl = 1;
		delay(5);
		scl = 0;
		sda = 1;
		return dat;
}
void i2c_stop(){
	scl = 0;
	sda = 0;
	delay(5);
	scl = 1;
	delay(5);
	sda = 1;
}
void eeprom_wait(unsigned char dev_addr){
	bit ack;
	do{
		i2c_start();
		ack = i2c_write(dev_addr);
		i2c_stop();
	}while(!ack);
}
void main(){
	unsigned char ch[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	unsigned int k = 0;
	unsigned int page_cnt = 0;
	unsigned char addr = 0x00;
	unsigned char dev_addr = 0xA0;
	unsigned char c;
	// writing data into EEPROM
	while(1){
			i2c_start();
			i2c_write(dev_addr);
			i2c_write(addr);
			page_cnt = 0;
			while(page_cnt<16){
				i2c_write(ch[k]);
				page_cnt++;
				addr++;
				if(ch[k] == '\0') break;
				k++;
			}
			i2c_stop();
			eeprom_wait(dev_addr);
			if(ch[k] == '\0') break;
			if(addr>0xFF){
				addr = 0x00;
				dev_addr = 0xA2;
			}
	}
	//reading data from EEPROM
	i2c_start();
	i2c_write(0xA0);
	i2c_write(0x00);
	i2c_start();
	i2c_write(0xA1);
	
	while(1){
		c = i2c_read(1);
		if(c==0){ i2c_read(0); break;}
	}
	i2c_stop();
	while(1);
}