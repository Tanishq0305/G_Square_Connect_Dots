/*
 * File:   newmain.c
 * Author: hrish
 *
 * Created on 25 July, 2024, 12:20 PM
 */

// CONFIG1H
#pragma config OSC = HS         // Oscillator (HS oscillator)
#pragma config OSCS = OFF       // Osc. Switch Enable (Oscillator system clock switch option is disabled (main oscillator is source))

// CONFIG2L
#pragma config PWRT = OFF       // Power Up Timer (PWRT disabled)
#pragma config BOR = ON         // Brown Out Detect (Brown-out Reset enabled)
#pragma config BORV = 20        // Brown Out Voltage (VBOR set to 2.0V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Postscaler (1:32768)

// CONFIG3L

// CONFIG3H
#pragma config CCP2MX = OFF     // CCP2 Mux (CCP2 input/output is multiplexed with RE7)
#pragma config MCLRE = OFF      // MCLR enable (RG5 input enabled, MCLR disabled)

// CONFIG4L
#pragma config STVR = OFF       // Stack Overflow Reset (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Low Voltage Program (Low-voltage ICSP disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protect 000800-0003FFF (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protect 0004000-007FFF (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protect 008000-00BFFF (Block 2 (008000-00BFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Code Protect Boot (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EE Read Protect (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Table Write Protect 00800-003FFF (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Table Write Protect 004000-007FFF (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Table Write Protect 08000-0BFFF (Block 2 (008000-00BFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Config. Write Protect (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Table Write Protect Boot (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EE Write Protect (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protect 00800-003FFF (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protect 004000-07FFF (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protect 08000-0BFFF (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Table Read Protect Boot (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>

#define _XTAL_FREQ 4000000
void main(void) {
    TRISB=0X00;
    while(1)
    {
        PORTBbits.RB0 ^=1;
        __delay_ms(500);
    }
    return;
}
