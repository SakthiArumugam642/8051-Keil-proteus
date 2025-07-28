#include <reg51.h>
#include <stdio.h>

sbit rs = P3^0;
sbit rw = P3^1;
sbit en = P3^2;

void debounce_delay() {
    unsigned int i;
    for (i = 0; i < 1275; i++);
    for (i = 0; i < 125; i++);
}

void lcd_cmd(unsigned char ch) {
    P2 = ch;
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
    P2 = ch;
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
void main() {
    char buf[10];
    unsigned int val;
    unsigned int i = 100;

    lcd_init();
    lcd_cmd(0x01);
    lcd_string("Ready !!!");
    while(i--) debounce_delay();

    lcd_cmd(0x01);
    TMOD = 0x06;  // Timer0, Mode 2 (8-bit auto-reload)
    TH0 = 0x00;
    TL0 = 0x00;
    TR0 = 1;

    while(1) {
        val = TL0;
        sprintf(buf, "Count: %d", val);
        lcd_string(buf);
				lcd_cmd(0x80);
				debounce_delay();
    }
}
