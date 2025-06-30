#include <reg51.h>
#include <stdio.h>

unsigned int stop_time = 0;
unsigned long total_ticks = 0;
float time = 0;
unsigned int overflow_count = 0;

sbit control_pin = P2^0;
sbit rs = P2^5;
sbit rw = P2^6;
sbit en = P2^7;

void debounce_delay() {
    unsigned int i;
    for (i = 0; i < 1275; i++);
    for (i = 0; i < 125; i++);
}

void start_timer() {
    TMOD = 0x01;     // Timer0, Mode1 (16-bit)
    TH0 = 0x00;
    TL0 = 0x00;
    overflow_count = 0;  // Reset overflow count
    TF0 = 0;        // Clear overflow flag
    ET0 = 1;        // Enable Timer0 interrupt
    EA = 1;         // Enable global interrupts
    TR0 = 1;        // Start Timer0
}

void stop_timer() {
    TR0 = 0;        // Stop Timer0
    ET0 = 0;        // Disable Timer0 interrupt
}

void lcd_cmd(unsigned char ch) {
    P3 = ch;
    rs = 0;
    rw = 0;
    en = 1;
    debounce_delay();
    en = 0;
}

void lcd_init() {
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
}

void lcd_data(unsigned char ch) {
    P3 = ch;
    rs = 1;
    rw = 0;
    en = 1;
    debounce_delay();
    en = 0;
}

void lcd_string(char *ch) {
    unsigned int k = 0;
    while (ch[k] != '\0') {
        lcd_data(ch[k++]);
    }
}

void calculate_time() {
    char buf[20];
    stop_time = (TH0 << 8) | TL0;

    total_ticks = ((unsigned long)overflow_count * 65536UL) + stop_time;

    time = total_ticks / 1085000.0;

    sprintf(buf, "Time: %.4f Sec", time);
    lcd_cmd(0x01);
    lcd_string(buf);
}


void timer0_ISR(void) interrupt 1 {
    overflow_count++;   
}

void main() {
    bit sts = 0;
    lcd_init();
    lcd_cmd(0x01);
    lcd_string("Ready !!!");
    debounce_delay();

    while (1) {
        if (control_pin == 0) {
            debounce_delay();
            if (control_pin == 0) {
                if (sts == 0) {
                    lcd_cmd(0x01);
                    lcd_string("Press again !");
                    debounce_delay();
                    start_timer();
                    sts = 1;
                } else {
                    stop_timer();
                    sts = 0;
                    calculate_time();
                }
                while (control_pin == 0)
                    debounce_delay(); 
            }
        }
    }
}
