#include <reg51.h>

sbit in1 = P3^4;   // Fan input pin
sbit en  = P3^5;   // Enable pin for fan
sbit lamp = P3^6;  // Light control pin

unsigned int mode = 0;  // Stores selected fan speed (PWM duty cycle)
bit fan_on = 0;         // Fan state ON/OFF
unsigned int duty_counter = 0; 

// --- UART Setup ---
void UART_init() {
    TMOD |= 0x20;   // Timer1 Mode 2 (auto-reload)
    SCON = 0x50;    // UART mode 1, 8-bit data, REN enabled
    TH1 = 0xFD;     // 9600 baud @ 11.0592MHz
    TR1 = 1;
}

void put_char(char ch) {
    SBUF = ch;
    while (TI == 0);
    TI = 0;
}

void put_str(char *ch) {
    while (*ch) {
        put_char(*ch);
        ch++;
    }
}

unsigned char get_char() {
    while (RI == 0);
    RI = 0;
    put_char(SBUF);
    return SBUF;
}

void get_str(char *buffer) {
    char ch;
    unsigned int i = 0;
    while (1) {
        ch = get_char();
        if (ch == '\r' || ch == '\n') {
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
    while (*buffer) {
        num = num * 10 + (*buffer - '0');
        buffer++;
    }
    return num * sign;
}

void clear_buffer(char *buf, int size) {
    int i;
    for (i = 0; i < size; i++) buf[i] = 0;
}

// --- Timer0 for PWM ---
void Timer0_ISR(void) interrupt 1 {
    TH0 = 0xFF;  // ~1ms tick (11.0592 MHz)
    TL0 = 0x9C;

    if (fan_on) {
        duty_counter++;
        if (duty_counter >= 100) duty_counter = 0;

        // Duty cycle control
        if (mode == 1) {            // 25%
            if (duty_counter < 25) { in1 = en = 1; }
            else { in1 = en = 0; }
        }
        else if (mode == 2) {       // 50%
            if (duty_counter < 50) { in1 = en = 1; }
            else { in1 = en = 0; }
        }
        else if (mode == 3) {       // 75%
            if (duty_counter < 75) { in1 = en = 1; }
            else { in1 = en = 0; }
        }
        else if (mode == 4) {       // 100%
            in1 = en = 1;
        }
    }
    else {
        in1 = en = 0;   // Fan OFF
    }
}

// --- Main Code ---
int main() {
    unsigned char buffer[20];
    unsigned int opt, opt1;

    // Timer0 init for PWM
    TMOD |= 0x01;   // Timer0 mode 1 (16-bit)
    TH0 = 0xFF;
    TL0 = 0x9C;
    ET0 = 1;        // Enable Timer0 interrupt
    EA = 1;         // Enable global interrupt
    TR0 = 1;        // Start Timer0

    UART_init();
    lamp = 0;   // Light OFF initially
    in1 = en = 0;

    while (1) {
        put_str("\r\n__Home Appliance Menu__\r\n");
        put_str("1. Light\r\n");
        put_str("2. Fan\r\n");
        put_str("Enter the option: ");
        get_str(buffer);
        opt = str_to_int(buffer);
        clear_buffer(buffer, 20);

        // --- MAIN MENU HANDLING ---
        if (opt == 1) {
            put_str("\r\n__Light ON/OFF__\r\n");
            put_str("1. ON\r\n");
            put_str("2. OFF\r\n");
            put_str("Enter the option: ");
            get_str(buffer);
            opt1 = str_to_int(buffer);
            clear_buffer(buffer, 20);

            if (opt1 == 1) lamp = 1;
            else if (opt1 == 2) lamp = 0;
            else put_str("\r\nInvalid Light Option!\r\n");
        }

        else if (opt == 2) {
            put_str("\r\n__Fan ON/OFF__\r\n");
            put_str("1. ON\r\n");
            put_str("2. OFF\r\n");
            put_str("Enter the option: ");
            get_str(buffer);
            opt1 = str_to_int(buffer);
            clear_buffer(buffer, 20);

            if (opt1 == 1) {
                fan_on = 1;

                put_str("\r\n__Speed Level__\r\n");
                put_str("1 - 25%\r\n");
                put_str("2 - 50%\r\n");
                put_str("3 - 75%\r\n");
                put_str("4 - 100%\r\n");
                put_str("Enter speed: ");
                get_str(buffer);
                mode = str_to_int(buffer);
                clear_buffer(buffer, 20);

                if (mode < 1 || mode > 4) {
                    put_str("\r\nInvalid Speed Option!\r\n");
                    fan_on = 0;
                    in1 = en = 0;
                }
            }
            else if (opt1 == 2) {
                fan_on = 0;
                in1 = en = 0;
            }
            else {
                put_str("\r\nInvalid Fan Option!\r\n");
            }
        }
        else {
            put_str("\r\nInvalid Main Menu Option!\r\n");
        }
    }
}
