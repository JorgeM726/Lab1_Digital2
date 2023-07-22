/*
 * File:   display.c
 * Author: jmuni
 *
 * Created on July 21, 2023, 4:59 PM
 */

#include <xc.h>
#include <stdint.h>
#include "display.h"
#define _XTAL_FREQ 4000000

unsigned char display[] = 
{
    0b11000000,	    // 0	    
	0b11111001,	    // 1	    
	0b10100100,	    // 2	    
	0b10110000,	    // 3	    
	0b10011001,	    // 4	    
	0b10010010,	    // 5	    
	0b10000010,	    // 6
	0b11111000,	    // 7
	0b10000000,	    // 8
	0b10011000,    //9
    0b10001000,	    // A
	0b10000011,	    // B
	0b11000110,	    // C
	0b10100001,	    // D
	0b10000110,     //E
	0b10001110,     // F
};

disp_array(int posicion){
    return display[posicion];
}

