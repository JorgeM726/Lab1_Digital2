#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits Write protection off)
       
#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 4000000
#include "IOCB.h"
#include "ADC.h"
         

unsigned int numero = 0;
unsigned int numero2 = 0;
void setup(void);
unsigned int cont = 0; 

void __interrupt() isr (void){
    
     if (INTCONbits.RBIF){
        
        if (PORTBbits.RB0==0){ 
            PORTD++;
            cont ++;
        } 
        
        else if (PORTBbits.RB1 ==0){ 
            PORTD--;
            cont--;
        } 
        
        
        INTCONbits.RBIF=0;
    }
    
     if(PIR1bits.ADIF){              // Revisar interrupción de ADC
        if(adc_get_channel() == 0){    // Revisar canal 12
            numero = adc_read();          // Mostrar conversión en PORTA
        }
        
        else 
            numero2 = adc_read();            //Enviar número a display si es en el canal 10
            PIR1bits.ADIF = 0;          // limpiar interrupción
    }
    return;
}

void main(void) {
    setup();
    __delay_us(50);
    ADCON0bits.GO = 1;
    while(1){
        
        //Envío a displays
        PORTC = disp_array(numero & 0x0F);
        PORTE = 0B001;
        __delay_ms(10);
        PORTE = 0B000;
        
        PORTC = disp_array((numero >> 4) & 0x0F);
        PORTE = 0B010;
        __delay_ms(10);
        PORTE = 0B000;
        
       
      if(ADCON0bits.GO == 0){                 
            if(adc_get_channel() == 0) {   
                adc_change_channel(1);    // Cambio de canal
            }
            else
                adc_change_channel(0);    // Cambio de canal
            
                __delay_us(100);                 // Tiempo de adquisicion
                ADCON0bits.GO = 1;              // Iniciar conversion
        }
        
        if(numero > cont){
            PORTBbits.RB7=1;
        }else
            PORTBbits.RB7 =0;
    }
    return;
}

void setup(void){
    
    ANSEL = 0b00000011; 
    ANSELH = 0; 
    TRISE = 0;
    TRISD = 0x00;
    PORTD = 0;
    TRISA = 0XFF;
    PORTA = 0;
    ioc_init(0x7F);
    TRISC =0x00;
    PORTC = 0;
    
    adc_init(0);
    
    
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0; 
    
     // CONFIGURACION DEL OSCILADOR
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0; // 4MHZ
    OSCCONbits.SCS = 1;  // OSCILADOR INTERNO 
    
    
                      
     
    
    // CONFIGURACION INTERRUPCIONES
   
    
    INTCONbits.PEIE = 1;        // Int. de perifericos
    INTCONbits.GIE = 1;         // Int. globales
    
}

