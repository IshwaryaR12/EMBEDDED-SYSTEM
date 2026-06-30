
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
#include <string.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000
#define lcd PORTB
#define RS RD5
#define RW RD6
#define E  RD7
#define S1  RC3
#define S2  RC4
#define Metal_sensor RA0
#define PLASTIC_sensor RA1
#define PVC_sensor RA2
#define BUZZ RA5

#define ADDR_METAL   0x10
#define ADDR_PLASTIC 0x11
#define ADDR_PVC     0x12

char RF_BUFF[20];

void LCD_Init();
void send_cmd(char b);
void show_data(const char *s);
void send_data(char a);
void UART_Init();
void UART_Read_String(char *buffer, int max_len);
void eeprom_write(unsigned char addr, unsigned char data);
unsigned char eeprom_read(unsigned char addr);
void Servo_SetAngle(unsigned int angle);
void Process_Detection(const char* name, unsigned char addr);
void Show_All_Counts();
void Clear_System_Counts();

int Rfid_Turn=0;
void main() {
    TRISB=0x00;
    TRISD=0x00;
    TRISC2=0;
    TRISC6=0;
    TRISC7=1;
     TRISA0=1;
     TRISA1=1;
     TRISA2=1;
     TRISA5=0;
     TRISC3=1;
     TRISC4=1;
     ADCON1=0x06;
    LCD_Init();
    UART_Init();
    BUZZ=0;
    if(eeprom_read(ADDR_METAL) == 0xFF) eeprom_write(ADDR_METAL, 0);
    if(eeprom_read(ADDR_PLASTIC) == 0xFF) eeprom_write(ADDR_PLASTIC, 0);
    if(eeprom_read(ADDR_PVC) == 0xFF) eeprom_write(ADDR_PVC, 0);

    send_cmd(0x01);
    show_data("WAITING FOR");
    send_cmd(0xc0);
    show_data("OBJECT");
    __delay_ms(1500);
//    if(S1==0) 
//        {
//           Show_All_Counts();
//        }
//        else if(S2==0) 
//        {
//           Clear_System_Counts();
//        }
    while(1) {
        send_cmd(0x01);
        show_data("SCANNING...");
        __delay_ms(2000);
        int Sensor_Turn=1;
        if(S1==0) 
        {
           Show_All_Counts();
        }
        else if(S2==0) 
        {
           Clear_System_Counts();
        }
        if(RCIF==1)
        {
        UART_Read_String(RF_BUFF, 20); 
        if(strcmp(RF_BUFF,"METAL_101") == 0) 
        {
            Process_Detection("Metal Detected", ADDR_METAL);        
            Servo_SetAngle(0);
            __delay_ms(3000);
        }
        else if(strcmp(RF_BUFF, "PLASTIC_101") == 0)
        {
            Process_Detection("Plastic Detect", ADDR_PLASTIC);           
            Servo_SetAngle(90);
            __delay_ms(3000);
        }
        else if(strcmp(RF_BUFF,"PVC_101") == 0) 
        {
            Process_Detection("PVC Detected", ADDR_PVC);
            Servo_SetAngle(180);
           __delay_ms(3000);
        }
        else if(strcmp(RF_BUFF,"TAG_000")==0)
        {
            BUZZ=1;
            __delay_ms(1500);
            BUZZ=0;
            send_cmd(0x01);
            show_data("TAG NOT");
            send_cmd(0xC0);
            show_data("Detected");
            __delay_ms(2000);
        while(Sensor_Turn)
        {
            while(Metal_sensor==1 && PLASTIC_sensor ==1 && PVC_sensor ==1);
        if(Metal_sensor==0)
        {
            Process_Detection("Metal Detected", ADDR_METAL);
            Servo_SetAngle(0);
            __delay_ms(5000);
            Sensor_Turn=0;
        }
        if(PLASTIC_sensor==0)
        {
            Process_Detection("PLASTIC Detected", ADDR_PLASTIC);
            Servo_SetAngle(90);
            __delay_ms(5000);
            Sensor_Turn=0;
        }
        if(PVC_sensor==0)
        {
            Process_Detection("PVC Detected", ADDR_PVC);
            Servo_SetAngle(180);
            __delay_ms(5000);
            Sensor_Turn=0;
        }
        
      }
        }
        
//        memset(RF_BUFF, 0, sizeof(RF_BUFF)); 
    }
        memset(RF_BUFF, 0, sizeof(RF_BUFF)); 
}
}


void Process_Detection(const char* name, unsigned char addr) 
{
    unsigned char count = eeprom_read(addr);
    count++;
    eeprom_write(addr, count);
    
    send_cmd(0x01);
    show_data(name);
    
    char buf[16];
    sprintf(buf, "Total: %d", count);
    send_cmd(0xC0);
    show_data(buf);
    __delay_ms(2000);
}

void Show_All_Counts() {
    char buf[16];
    send_cmd(0x01);
    show_data("MASTER REPORT");
    __delay_ms(2000);

    sprintf(buf, "M:%d P:%d", eeprom_read(ADDR_METAL), eeprom_read(ADDR_PLASTIC));
    send_cmd(0x01); 
    show_data(buf);
    
    sprintf(buf, "PVC Count: %d", eeprom_read(ADDR_PVC));
    send_cmd(0xC0); 
    show_data(buf);
    __delay_ms(4000);
}

void Clear_System_Counts() {
    send_cmd(0x01);
    show_data("clear DATA...");
    eeprom_write(ADDR_METAL, 0);
    eeprom_write(ADDR_PLASTIC, 0);
    eeprom_write(ADDR_PVC, 0);
    __delay_ms(1500);
}

void UART_Read_String(char *buffer, int max_len) {
//    int Sensor_Turn=0;
//    int Rfid_Turn=0;
    int i = 0;
    while (i < max_len - 1) {
        if (OERR) {
            CREN = 0; 
            CREN = 1;
        }
        
        while (!RCIF);
        char rx = RCREG;
        
        if (rx == '\r' || rx == '\n') break;
        buffer[i++] = rx;
    }
    buffer[i] = '\0';
    
    
}

void UART_Init() {
    SPBRG = 25; 
    TXSTA = 0x24; 
    RCSTA = 0x90;
}

void eeprom_write(unsigned char addr, unsigned char data) {
    while(WR);
    EEADR = addr; 
    EEDATA = data; 
    EEPGD = 0; 
    WREN = 1;
    GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA; 
    WR = 1; 
    GIE = 1;
    WREN = 0;
}

unsigned char eeprom_read(unsigned char addr) {
    EEADR = addr; 
    EEPGD = 0; 
    RD = 1;
    return EEDATA;
}

void Servo_SetAngle(unsigned int angle) {
    unsigned int pulse; 
//    = 1000 + (unsigned int)(angle * 5.5);
//    for(int i=0; i<50; i++) {
//        RC2 = 1;
//        __delay_ms(1000);
//       for(int j=0; j < (pulse/10); j++)
//       {
////           __delay_us(10);
//       }
//       RC2=0;
//       __delay_ms(18);
//    }
    if(angle==0)
    {
        pulse=1000;
//        CCPR1L=6;
//        __delay_ms(100);
    }
    else if(angle==90)
    {
        pulse=1500;
//        CCPR1L=9;
//        __delay_ms(100);
    }
    else if(angle==180)
    {
        pulse=2000;
//        CCPR1L=12;
//        __delay_ms(100);
    }
    for(int i=0; i<50; i++) {
        RC2 = 1;
        if(pulse==1000)
        {
            __delay_us(485);
        }
        else if(pulse==1500)
        {
            __delay_us(1309);
        }
        else if(pulse==2000)
        {
            __delay_us(2135);
        }
        RC2=0;
        __delay_ms(18);
    }
//    __delay_ms(500);
}

void LCD_Init() {
    send_cmd(0x38);
	send_cmd(0x0e);
	send_cmd(0x01);
	send_cmd(0x06);
	send_cmd(0x80);
	send_cmd(0x0c);
}

void show_data(const char *s)
{
    while(*s)
    {
        send_data(*s++);
    }
}
void send_data(char a)
{
    lcd=a;
    RS=1;
    RW=0;
    E=1;
    __delay_ms(10);
    E=0;
}
void send_cmd(char b)
{
    lcd=b;
    RS=0;
    RW=0;
    E=1;
    __delay_ms(10);
    E=0;
}