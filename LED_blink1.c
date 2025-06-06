#include <reg52.h>

sbit pos = P1^0;
sbit sw  = P1^1;

void delay(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1275; j++); // Roughly 1ms delay
}

void main() {
    pos = 0;

    while(1) {
            //delay(20);            // Debounce
            if (sw == 1){
                pos = ~pos; 
              while(sw==1);// Wait for release
            }
        }
			}