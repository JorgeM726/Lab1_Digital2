/*
 * File:   ADC.c
 * Author: jmuni
 *
 * Created on July 18, 2023, 4:18 PM
 */


#include <xc.h>
#include <stdint.h>
#include "ADC.h"
#define _XTAL_FREQ 4000000

adc_init(int channel){
    
     // CONFIGURACION ADC
    ADCON0bits.ADCS = 0b01;             // Fosc/8
    ADCON1bits.VCFG0 = 0;               // VDD
    ADCON1bits.VCFG1 = 0;               // VSS
    ADCON0bits.CHS = channel;                // Canal del usuario  
    ADCON1bits.ADFM = 0;        // Justificado a la izquierda
    __delay_us(50);             // Sample time
    ADCON0bits.ADON = 1;        // HAbilitar modulo ADC
    PIR1bits.ADIF = 0;          
    PIE1bits.ADIE = 1;          // Int. de ADC
    
}

int adc_read(){
    return ADRESH;
}

adc_change_channel(int channel){
    
    ADCON0bits.CHS = channel;    // Cambio de canal

}

int adc_get_channel(){
    
    return  ADCON0bits.CHS;
}