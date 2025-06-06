#include <reg51.h>

sbit pos = P1^0;  // Correct: Use P1 (not p1)


void delay(unsigned int n) {
    unsigned int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 1275; j++);  // Approx. 1ms delay for 11.0592 MHz
}

void main() {
    while (1) {
        pos = 1;     // Turn ON pos (P1.0)
       delay(1000); // 1 second delay
        pos = 0;     // Turn OFF pos
        delay(1000); // 1 second delay
    }
}
