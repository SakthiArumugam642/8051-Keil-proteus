#include <reg51.h>
#include <stdio.h>

void uart_init() {
    TMOD = 0x20;
    TH1 = 0xFD;      // 9600 baud @ 11.0592 MHz
    SCON = 0x50;
    TR1 = 1;
}

void send_char(unsigned char ch) {
    SBUF = ch;
    while(TI == 0);
    TI = 0;
}

void send_str(char *ch) {
    while(*ch) {
        send_char(*ch);
        ch++;
    }
}

unsigned char char_receive() {
    while(RI == 0);
    RI = 0;
    send_char(SBUF);   // echo back
    return SBUF;
}

void clear_buffer(char *buf, int size) {
    int i;
    for (i = 0; i < size; i++) {
        buf[i] = 0;
    }
}

void str_receive(char *buffer) {
    char ch;
    unsigned int i = 0;
    while(1) {
        ch = char_receive();
        if(ch == '\r' || ch == '\n') {
						buffer[i] = 0;
						break;
				}
        buffer[i++] = ch;
    }
}

int str_to_int(char *buffer) {
    int num = 0;
    int sign = 1;
    if (*buffer == '-') { sign = -1; buffer++; }
    while(*buffer) {
        num = num * 10 + (*buffer - '0');
        buffer++;
    }
    return num * sign;
}

float str_to_float(char *buffer) {
    float num = 0;
    float frac = 0;
    int divisor = 1;
    int sign = 1;
    char after_dot = 0;

    if (*buffer == '-') { sign = -1; buffer++; }

    while (*buffer) {
        if (*buffer == '.') {
            after_dot = 1;
        } else {
            num = num * 10 + (*buffer - '0');
            if (after_dot) divisor *= 10;
        }
        buffer++;
    }
    return sign * (num / divisor);
}

void send_int(int num) {
    char buf[10];
    int i = 0, j;
    if (num == 0) {
        send_char('0');
        return;
    }
    if (num < 0) {
        send_char('-');
        num = -num;
    }
    while (num > 0) {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }
    for (j = i - 1; j >= 0; j--) {
        send_char(buf[j]);
    }
}

void send_float(float num) {
    int int_part, frac_part;
    if (num < 0) {
        send_char('-');
        num = -num;
    }
    int_part = (int)num;
    send_int(int_part);
    send_char('.');
    num = num - int_part;
    num *= 100; // 2 decimal places
    frac_part = (int)(num + 0.5);
    if (frac_part < 10) send_char('0');
    send_int(frac_part);
}

void main() {
    char buffer[20];
    int i1, i2;
    float f1, f2;
    int choice;

    uart_init();

    while(1) {
        send_str("\r\n=== CALCULATOR MENU ===\r\n");
        send_str("1. Integer Addition\r\n");
        send_str("2. Integer Subtraction\r\n");
        send_str("3. Integer Multiplication\r\n");
        send_str("4. Float Addition\r\n");
        send_str("5. Float Subtraction\r\n");
        send_str("6. Float Multiplication\r\n");
        send_str("Enter choice: ");

        str_receive(buffer);
        choice = str_to_int(buffer);
				clear_buffer(buffer, 20);

        if(choice >= 1 && choice <= 3) {
            send_str("Enter 1st integer: ");
            str_receive(buffer);
            i1 = str_to_int(buffer);
						clear_buffer(buffer, 20);

            send_str("Enter 2nd integer: ");
            str_receive(buffer);
            i2 = str_to_int(buffer);
						clear_buffer(buffer, 20);
					
            send_str("Result: ");
            if(choice == 1) send_int(i1 + i2);
            if(choice == 2) send_int(i1 - i2);
            if(choice == 3) send_int(i1 * i2);
            send_str("\r\n");

        } else if(choice >= 4 && choice <= 6) {
            send_str("Enter 1st float: ");
            str_receive(buffer);
            f1 = str_to_float(buffer);
						clear_buffer(buffer, 20);
					
            send_str("Enter 2nd float: ");
            str_receive(buffer);
            f2 = str_to_float(buffer);
						clear_buffer(buffer, 20);
						
            send_str("Result: ");
            if(choice == 4) send_float(f1 + f2);
            if(choice == 5) send_float(f1 - f2);
            if(choice == 6) send_float(f1 * f2);
            send_str("\r\n");

        } else {
            send_str("Invalid choice\r\n");
        }
    }
}
