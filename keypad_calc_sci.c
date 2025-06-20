#include <reg52.h>
#include <stdio.h>
#include <math.h>

sbit r1 = P2^0;
sbit r2 = P2^1;
sbit r3 = P2^2;
sbit r4 = P2^3;
sbit c1 = P2^4;
sbit c2 = P2^5;
sbit c3 = P2^6;
sbit c4 = P2^7;
sbit c5 = P3^0;
sbit c6 = P3^1;

sbit rs = P3^7;
sbit rw = P3^6;
sbit en = P3^5;

bit last_equal = 0;
float memory = 0;
bit mrc_flag = 0;
float num1 = 0, num2 = 0, res = 0;
char op = 0;
bit oper_sts = 0;
bit dec_mode1 = 0, dec_mode2 = 0;
float dec_factor1 = 0.1, dec_factor2 = 0.1;
char key;

void delay(unsigned int a) {
    unsigned int i, j;
    for (i = 0; i < a; i++)
        for (j = 0; j < 100; j++);
}

void lcd_cmd(unsigned char ch) {
    P1 = ch;
    rs = 0; rw = 0; en = 1;
    delay(70);
    en = 0;
}

void lcd_data(unsigned char ch) {
    P1 = ch;
    rs = 1; rw = 0; en = 1;
    delay(70);
    en = 0;
}

void lcd_print_float(float val) {
    char buf[16];
	int i;
    sprintf(buf, "%.3f", val);
    for (i = 0; buf[i] != '\0'; i++) {
        lcd_data(buf[i]);
    }
}

void lcd_init() {
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
}

/*float my_sqrt(float n) {
    float x = n;
    float y = 1;
    float e = 0.0001; // acceptable error

    while (x - y > e) {
        x = (x + y) / 2;
        y = n / x;
    }

    return x;
}*/

char getkey() {
    unsigned char keypad[4][6] = {
        {'C','7','8','9','*','/'},
        {'x','4','5','6','-','r'},
        {'%','1','2','3','+','n'},
        {'s','0','.','=','+','p'}
    };

    while (1) {
        r1 = 0; r2 = r3 = r4 = 1;
        if (c1 == 0) { delay(50); while(c1==0); return keypad[0][0]; }
        if (c2 == 0) { delay(50); while(c2==0); return keypad[0][1]; }
        if (c3 == 0) { delay(50); while(c3==0); return keypad[0][2]; }
        if (c4 == 0) { delay(50); while(c4==0); return keypad[0][3]; }
        if (c5 == 0) { delay(50); while(c5==0); return keypad[0][4]; }
        if (c6 == 0) { delay(50); while(c6==0); return keypad[0][5]; }

        r2 = 0; r1 = r3 = r4 = 1;
        if (c1 == 0) { delay(50); while(c1==0); return keypad[1][0]; }
        if (c2 == 0) { delay(50); while(c2==0); return keypad[1][1]; }
        if (c3 == 0) { delay(50); while(c3==0); return keypad[1][2]; }
        if (c4 == 0) { delay(50); while(c4==0); return keypad[1][3]; }
        if (c5 == 0) { delay(50); while(c5==0); return keypad[1][4]; }
        if (c6 == 0) { delay(50); while(c6==0); return keypad[1][5]; }

        r3 = 0; r1 = r2 = r4 = 1;
        if (c1 == 0) { delay(50); while(c1==0); return keypad[2][0]; }
        if (c2 == 0) { delay(50); while(c2==0); return keypad[2][1]; }
        if (c3 == 0) { delay(50); while(c3==0); return keypad[2][2]; }
        if (c4 == 0) { delay(50); while(c4==0); return keypad[2][3]; }
        if (c5 == 0) { delay(50); while(c5==0); return keypad[2][4]; }
        if (c6 == 0) { delay(50); while(c6==0); return keypad[2][5]; }

        r4 = 0; r1 = r2 = r3 = 1;
        if (c1 == 0) { delay(50); while(c1==0); return keypad[3][0]; }
        if (c2 == 0) { delay(50); while(c2==0); return keypad[3][1]; }
        if (c3 == 0) { delay(50); while(c3==0); return keypad[3][2]; }
        if (c4 == 0) { delay(50); while(c4==0); return keypad[3][3]; }
        if (c5 == 0) { delay(50); while(c5==0); return keypad[3][4]; }
        if (c6 == 0) { delay(50); while(c6==0); return keypad[3][5]; }
    }
}

void main() {
    lcd_init();
    delay(100);
    lcd_cmd(0x01);

    while (1) {
        key = getkey();

        if (key >= '0' && key <= '9') {
            if (last_equal && !oper_sts) {
                num1 = 0; res = 0; dec_mode1 = 0; dec_factor1 = 0.1; last_equal = 0;
            }
            lcd_data(key);
            if (!oper_sts) {
                if (!dec_mode1)
                    num1 = num1 * 10 + (key - '0');
                else {
                    num1 += (key - '0') * dec_factor1;
                    dec_factor1 *= 0.1;
                }
            } else {
                if (!dec_mode2)
                    num2 = num2 * 10 + (key - '0');
                else {
                    num2 += (key - '0') * dec_factor2;
                    dec_factor2 *= 0.1;
                }
            }
        } 
else if (key == 'p') { // M+
    float val = last_equal ? res : (oper_sts ? num2 : num1);
    memory += val;
    mrc_flag = 0;
}

else if (key == 'n') { // M-
    float val = last_equal ? res : (oper_sts ? num2 : num1);
    memory -= val;
    mrc_flag = 0;
}

else if (key == 'r') { // MRC
    lcd_cmd(0x01);
    lcd_print_float(memory);
    delay(1500);
    lcd_cmd(0x01);

    if (mrc_flag) {
        memory = 0;
        mrc_flag = 0;
    } else {
        mrc_flag = 1;
    }
}

else if (key == 's') { // v key
    float sqrt_val;
	lcd_data('s');
    if (!oper_sts) {
        if (num1 >= 0) {
            sqrt_val = sqrt(num1);
            num1 = sqrt_val;
        } else {
            sqrt_val = 0; // or show error
        }
    } else {
        if (num2 >= 0) {
            sqrt_val = sqrt(num2);
            num2 = sqrt_val;
        } else {
            sqrt_val = 0;
        }
    }
		/*lcd_cmd(0x01);
    lcd_print_float(sqrt_val);
    delay(1500);
    lcd_cmd(0x01);*/

}
 else if (key == 'x') {
            lcd_data('!');
            if (!oper_sts) num1 = -num1;
            else num2 = -num2;
        } 
 else if (key == '%') {
            lcd_data('%');
            if (!oper_sts) num1 /= 100.0;
            else num2 /= 100.0;
        } 
 else if (key == '.') {
            lcd_data('.');
            if (!oper_sts) dec_mode1 = 1;
            else dec_mode2 = 1;
        } 
 else if (key == '+' || key == '-' || key == '*' || key == '/') {
    if (oper_sts) {
        switch (op) {
            case '+': res = num1 + num2; break;
            case '-': res = num1 - num2; break;
            case '*': res = num1 * num2; break;
            case '/': res = (num2 != 0) ? num1 / num2 : 0; break;
        }

        // Use result as num1 for next operation
        num1 = res;
        num2 = 0;
        dec_mode2 = 0;
        dec_factor2 = 0.1;
    }

    lcd_data(key);
    op = key;
    oper_sts = 1;
    last_equal = 0;
} 
 else if (key == '=') {
            switch (op) {
                case '+': res = num1 + num2; break;
                case '-': res = num1 - num2; break;
                case '*': res = num1 * num2; break;
                case '/': res = (num2 != 0) ? num1 / num2 : 0; break;
            }
            lcd_cmd(0x01);
            lcd_print_float(res);
            delay(2000);
            lcd_cmd(0x01);
            num1 = res; num2 = 0;
            dec_mode1 = dec_mode2 = 0;
            dec_factor1 = dec_factor2 = 0.1;
            oper_sts = 0; last_equal = 1;
        } 
 else if (key == 'C') {
            lcd_cmd(0x01);
            num1 = num2 = res = 0;
            oper_sts = 0;
            dec_mode1 = dec_mode2 = 0;
            dec_factor1 = dec_factor2 = 0.1;
        }
    }
}
