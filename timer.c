// Attempt to generate 50 ms T_on square wave using 8051 timer 0 and mode0,1,2


#include<reg51.h>

sbit p = P1^0;

/*
//Mode 0 - 13bit timer mode which has limited count like 256*32 ticks, widely used for lesser time delay works
//max time delay ~8.8ms
// since it was not auto reload we have to manually reload value for every count increments
   
void timer_init(){
		TMOD = 0x00;
		TH0 =0x00;
		TL0 = 0x02; 
		TR0 = 1;
}
void delay(unsigned int cnt){
		unsigned int count=0;
	while(count < cnt){
			TH0 =0x00;
			TL0 = 0x02;
			TF0 =0;
			while(TF0==0);
			count++;
	}
}
int main(){
	timer_init();
		while(1){
			p = ~p;
			delay(6);   // 6*8.19ms = 49.15ms 
		}

}
*/


/*
// Mode 1 - 16 bit timer mode which was widely used for generation of time delay, counter, square waves(pulse generation) etc...
// which has range of 256*256 ticks;
//max time delay ~70ms

void delay(){
		TMOD = 0x01;
		TH0 = 0x4b;
		TL0 = 0xfd;
		TR0 = 1;
		while(TF0 == 0);
		TF0 = 0;
		TR0 = 0;
}

int main(){
		while(1){
			p = ~p;
			delay();
		}
}


*/

/*
// Mode 2 - 8 bit auto reload mode where tl0 starts with tho value and once overflow occurs, tl0 again reloaded with th0 value
// hence no need of initialise again, also we cant change the value after overflow occurs;
// max time delay ~0.25ms

void timer_init(){
	TMOD = 0x02;
	TH0 = 0x06;
	TL0 = 0x06;
	TR0 = 1;
}
void delay(unsigned int cnt){
	unsigned int count = 0;
	while(count < cnt){
	while(TF0==0);
	TF0 =0;
	count++;
}
}

int main(){
	timer_init();
			while(1){
				p = ~p;
				delay(200); // 200*0.25ms = 50ms
			}
}

*/

// Mode 3 - split timer mode where TL0 is controlled by TR0/TF0 which act as a 8 bit timer independently
// And TH0 is controlled by TR1/TF1 which act as a 8 bit timer independently
// timer 1 is disabled in this particular mode


void TL0_init(){
	TL0 = 0x00;
	TR0 = 1;
}

void TH0_init(){
	TH0 = 0x00;
	TR1 = 1;
}

void delay_50msTL0(unsigned int cnt){
	unsigned int count =0;
	TL0_init();
	while(count <cnt){
			while(TF0== 0);
			TF0 =0;
			count++;
	}
}

void delay_50msTH0(unsigned int cnt){
	unsigned int count =0;
	TH0_init();
	while(count <cnt){
			while(TF1== 0);
			TF1 =0;
			count++;
	}
}

int main(){
	TMOD = 0x03;
	while(1){
		p = 1;
		delay_50msTL0(180); // 50000/(1.085*256) = 180
		p = 0;
		delay_50msTH0(180); // 50000/(1.085*256) = 180
	}

}
