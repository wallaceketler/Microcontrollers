/*
 * File:   newmain.c
 * Author: wallace
 *
 * Created on 8 de Abril de 2022, 11:30
 */

// PIC18F4550 Configuration Bit Settings

#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT didsabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define _XTAL_FREQ 4000000  //conferir freq adotada

char texto[16];
int temp_res = 0;
int temp_res2 = 0;

void main() {
    //no TRIS, 1 é entrada e 0 é saída
    
    ADCON1=0x06;//define uso apenas para entrada e saída digital
    TRISBbits.RB3 = 1;  //sensor alto -entrada
    TRISBbits.RB4 = 1;  //sensor baixo -entrada
    TRISCbits.RC0 = 0;  //válvula do alto - saída
    TRISEbits.RE0 = 0;  //válvula de baixo - saída
    TRISA = 0;          //define que display 4 da placa vai ser usado
    TRISD = 0;
    TRISCbits.RC2 = 0;
    PORTCbits.RC2 = 0;
    
    PORTBbits.RB3 = 1;  //define tudo desligado inicialmente menos válvula alta
    PORTBbits.RB4 = 1;  //o sensor não está ativo em 0
    PORTCbits.RC0 = 1;  //
    PORTEbits.RE0 = 0;  //
    PORTA = 0;          //define display resetado
    PORTD = 0;          //define segmentos desligados do display
    
    while(1){
        if(PORTBbits.RB3 == 0){ //se tiver em alto
            PORTA=0b00100000;//habilita display em caso de display multiplexado
            PORTD = 0b1110111;  //define display como A
            PORTCbits.RC0 = 0;  //desativa válvula do alto
            PORTEbits.RE0 = 1;  //ativa válvula do alto
            
            PORTCbits.RC2 = 1;
            __delay_ms(4000);
        }
        else{                   //se tiver em baixo
            PORTA=0b00100000;//habilita display em caso de display multiplexado
            PORTD = 0b1111001;  //define display como E
            PORTCbits.RC0 = 1;  //ativa válvula do alto
            PORTEbits.RE0 = 0;  //desativa válvula do baixo
            PORTCbits.RC2 = 0;
           
            __delay_ms(100);
        }
    }
}















//encher no início
//chega no sensor de cima
//mistura
//para de misturar
//abre valvula de saída
//encher de novo(...)
//sensor está ativado em zero
