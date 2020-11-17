//////////////////////////////////////////////////
// Comente esta linha para usar NIOS II - ECLIPSE
/////////////////////////////////////////////////

#define kit_picsimlab  



#ifdef kit_picsimlab  // Comandos apenas para MPLABX - PICSIMLAB
// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
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
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define alt_u8 unsigned char
#define alt_u16 unsigned int

#define HEX5_AVSB_BASE 10 //PORTA A
#define HEX4_AVSB_BASE 20 //PORTA B
#define LEDR_AVSB_BASE 30 //PORTA C
#define SW_AVSB_BASE 40 //PORTA D
#define LEDG_AVSB_BASE 50
#define _XTAL_FREQ 4000000


void usleep(alt_u16 tempo) {
    
    __delay_us(1000);
    
}

void LAT(alt_u8 porta, alt_u8 dado) {
    
    if (porta==10) LATA = dado;
    if (porta==20) LATB = dado;
    if (porta==30) LATC = dado;
    if (porta==40) LATD = dado;  
}

alt_u8 PORT(alt_u8 porta) {
    
    if (porta==10) return PORTA;
    if (porta==20) return PORTB;
    if (porta==30) return PORTC;
    if (porta==40) return PORTD; 
    return 0;
}

void setup_hw(void) {
    ADCON1 = 15;
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISD = 255;
}
#else  // Comandos apenas para NIOS II - ECLIPSE



#include "system.h"
#include "altera_avalon_pio_regs.h"

#include "alt_types.h"
#include "sys/alt_stdio.h"

//biblioteca para usar a função de atraso em microsegundos função => usleep("tempo_us")
#include <unistd.h>

//Comandos para leitura e escrita nas portas IO
#define PORT(base)		IORD_ALTERA_AVALON_PIO_DATA(base)
#define LAT(base, data)	IOWR_ALTERA_AVALON_PIO_DATA(base, data)


void setup_hw(void) {

}
#endif // Final dos comandos especificos


///////////////////////////////////////////////////////////////////////

void setup(void);
void setup_hw(void);
void loop(void);

void f_timers(void);
void f_timer1(void);
void f_timer2(void);
void f_timer3(void);

alt_u8 f_maq_n_primo_c(alt_u8 atual);
alt_u8 f_maq_n_primo_d(alt_u8 atual);
alt_u8 f_maq_n_3_c(alt_u8 atual);
alt_u8 f_maq_n_3_d(alt_u8 atual);
alt_u16 max_timer1, max_timer2, max_timer3;
alt_u8 sw, key, LEDR, seq=0, dir=0;
alt_u8 estado=1, dd=0, du=0, acelera;

int main() {
  setup_hw();
  setup();
  while (1) loop();
  return 0;
}


//1 = 000 0110 = 0x06
//2 = 101 1011 = 0x5b
//3 = 100 1111 = 0x4f
//4 = 110 0110 = 0x66
//5 = 110 1101 = 0x6d
//6 = 111 1101 = 0x7d
//7 = 000 0111 = 0x07
//8 = 111 1111 = 0x7f
//9 = 110 1111 = 0x6f

void setup(void) {
	max_timer1 = 20;
	max_timer2 = 50;
	//max_timer3 = 1000;
    seq=0;
    dir=0;
    acelera=0;

	LAT(HEX5_AVSB_BASE, 0x3f);
	LAT(HEX4_AVSB_BASE, 0x3f);
    LAT(LEDR_AVSB_BASE, 0b00000000);
    estado = f_maq_n_primo_c(estado);
}

void loop(void) {
    
	f_timers();
	usleep(1000);

}


void f_timers(void) {

	static alt_u16 c_timer1=0, c_timer2=0, c_timer3=0;
    
	if (c_timer1<max_timer1) {
		c_timer1++;
	}
	else {
		c_timer1=0;
		f_timer1();
	}

	if (c_timer2<max_timer2) {
			c_timer2++;
		}
		else {
			c_timer2=0;
			f_timer2();
		}

	if (c_timer3<max_timer3) {
			c_timer3++;
		}
		else {
			c_timer3=0;
			f_timer3();
		}

}

void f_timer1(void) {
	LAT(HEX5_AVSB_BASE, dd);
	LAT(HEX4_AVSB_BASE, du);
}

void f_timer2(void) {
    static alt_u8 vantd0=1, vantd1=1, vantre0=1;
    unsigned char vatual;
    vatual = RD0;
    if(vatual>vantd0){
         if(seq==0) seq=1;
    }
    if(vatual<vantd0){
        if(seq==1) seq=0;
    }
    vantd0 = vatual;
    
    vatual = RD1;
    if(vatual>vantd1){
        if(acelera==0) acelera=1;
    }
    if(vatual<vantd1){
        if(acelera==1) acelera=0;
    }
    vantd1 = vatual;
   
    
    vatual = RE0;
    if(vatual>vantre0){
        if(dir==0) dir=1; else dir=0; 
        } 
    vantre0 = vatual;
    
    if(acelera==0){
        max_timer3 = 1000;
    }
    if(acelera==1){
        max_timer3 = 500;
    }

}

void f_timer3(void) {
    
    if((seq==0) & (dir==0)){
        estado = f_maq_n_primo_c(estado);
         LAT(LEDR_AVSB_BASE, 0b00000000);
    }   
    if((seq==1) & (dir==0)){
        estado = f_maq_n_3_c(estado);
        LAT(LEDR_AVSB_BASE, 0b11110000);
    }
    if((seq==0) & (dir==1)){
        estado = f_maq_n_primo_d(estado);
        LAT(LEDR_AVSB_BASE, 0b00001111);
    }
    if((seq==1) & (dir==1)){
        estado = f_maq_n_3_d(estado);
        LAT(LEDR_AVSB_BASE, 0b11111111);
    }
    
}

alt_u8 f_maq_n_3_c(alt_u8 atual){

	alt_u8 prox;

	switch (atual) {
        
    case 1:
		prox = 2;
		dd = 0x00;
		du = 0x5b;
		break; 
        
	case 2:
		prox = 4;
		dd = 0x00;
		du = 0x66;
		break;
        
	case 4:
		prox = 5;
		dd = 0x00;
		du = 0x6d;
		break;

	case 5:
		prox = 7;
		dd = 0x00;
		du = 0x07;
		break;

	case 7:
		prox = 8;
		dd = 0x00;
		du = 0x7f;
		break;

	case 8:
		prox = 10;
		dd = 0x06;
		du = 0x3f;
		break;

	case 10:
		prox = 11;
		dd = 0x06;
		du = 0x06;
		break;

	case 11:
		prox = 13;
		dd = 0x06;
		du = 0x4f;
		break;

	case 13:
		prox = 14;
		dd = 0x06;
		du = 0x66;
		break;

	case 14:
		prox = 16;
		dd = 0x06;
		du = 0x7d;
		break;

	case 16:
		prox = 17;
		dd = 0x06;
		du = 0x07;
		break;
        
    case 17:
		prox = 19;
		dd = 0x06;
		du = 0x6f;
		break;  
        
    case 19:
		prox = 20;
		dd = 0x5b;
		du = 0x3f;
		break;
        
    case 20:
		prox = 22;
		dd = 0x5b;
		du = 0x5b;
		break;  
        
    case 22:
		prox = 23;
		dd = 0x5b;
		du = 0x4f;
		break;
        
    case 23:
		prox = 25;
		dd = 0x5b;
		du = 0x6d;
		break;
        
    case 25:
		prox = 26;
		dd = 0x5b;
		du = 0x7d;
		break;
        
    case 26:
		prox = 28;
		dd = 0x5b;
		du = 0x7f;
		break;
        
    case 28:
		prox = 29;
		dd = 0x5b;
		du = 0x6f;
		break;
        
    case 29:
		prox = 1;
		dd = 0x00;
		du = 0x06;
		break;    
        
	default:
		prox = 1;
		dd = 0x00;
		du = 0x06;
	}
	return prox;
}

alt_u8 f_maq_n_primo_c(alt_u8 atual){
    
    alt_u8 prox;

	switch (atual) {
      
    case 0:
		prox = 1;
		dd = 0x00;
		du = 0x06;
		break;     
        
    case 1:
		prox = 4;
		dd = 0x00;
		du = 0x66;
		break; 
        
	case 4:
		prox = 6;
		dd = 0x00;
		du = 0x7d;
		break;
        
	case 6:
		prox = 8;
		dd = 0x00;
		du = 0x7f;
		break;

	case 8:
		prox = 9;
		dd = 0x00;
		du = 0x6f;
		break;

	case 9:
		prox = 10;
		dd = 0x06;
		du = 0x3f;
		break;

	case 10:
		prox = 12;
		dd = 0x06;
		du = 0x5b;
		break;

	case 12:
		prox = 14;
		dd = 0x06;
		du = 0x66;
		break;

	case 14:
		prox = 15;
		dd = 0x06;
		du = 0x6d;
		break;

	case 15:
		prox = 16;
		dd = 0x06;
		du = 0x7d;
		break;

	case 16:
		prox = 18;
		dd = 0x06;
		du = 0x7f;
		break;

	case 18:
		prox = 20;
		dd = 0x5b;
		du = 0x3f;
		break;
        
    case 20:
		prox = 21;
		dd = 0x5b;
		du = 0x06;
		break;  
        
    case 21:
		prox = 22;
		dd = 0x5b;
		du = 0x5b;
		break;
        
    case 22:
		prox = 24;
		dd = 0x5b;
		du = 0x66;
		break;  
        
    case 24:
		prox = 25;
		dd = 0x5b;
		du = 0x6d;
		break;
        
    case 25:
		prox = 26;
		dd = 0x5b;
		du = 0x7d;
		break;
        
    case 26:
		prox = 27;
		dd = 0x5b;
		du = 0x07;
		break;
        
    case 27:
		prox = 28;
		dd = 0x5b;
		du = 0x7f;
		break;
        
    case 28:
		prox = 30;
		dd = 0x4f;
		du = 0x3f;
		break;
        
    case 30:
		prox = 0;
		dd = 0x00;
		du = 0x3f;
		break;    
        
	default:
		prox = 0;
		dd = 0x00;
		du = 0x3f;
	}
	return prox;
}

alt_u8 f_maq_n_primo_d(alt_u8 atual){
    alt_u8 prox;
    switch(atual){
        case 30:
            prox = 28;
            dd = 0x5b;
            du = 0x7f;
            break;
            
        case 28:
            prox = 27;
            dd = 0x5b;
            du = 0x07;
            break;
            
        case 27:
            prox = 26;
            dd = 0x5b;
            du = 0x7d;
            break;
            
        case 26:
            prox = 25;
            dd = 0x5b;
            du = 0x6d;
            break;
            
        case 25:
            prox = 24;
		dd = 0x5b;
		du = 0x66;
		break; 
        
        case 24:
            prox = 22;
            dd = 0x5b;
            du = 0x5b;
		break;
        
        case 22:
            prox = 21;
            dd = 0x5b;
            du = 0x06;
            break;  
            
        case 21:
            prox = 20;
            dd = 0x5b;
            du = 0x3f;
            break;
            
        case 20:
            prox = 18;
            dd = 0x06;
            du = 0x7f;
            break;
            
        case 18:
           prox = 16;
            dd = 0x06;
            du = 0x7d;
            break;
            
        case 16:
            prox = 15;
            dd = 0x06;
            du = 0x6d;
            break;
            
        case 15:
            prox = 14;
            dd = 0x06;
            du = 0x66;
            break;
            
        case 14:
            prox = 12;
            dd = 0x06;
            du = 0x5b;
            break;
            
        case 12:
           prox = 10;
            dd = 0x06;
            du = 0x3f;
            break;
            
        case 10:
            prox = 9;
            dd = 0x00;
            du = 0x6f;
            break;
            
        case 9:
            prox = 8;
            dd = 0x00;
            du = 0x7f;
            break;
            
        case 8:
            prox = 6;
            dd = 0x00;
            du = 0x7d;
            break;
            
        case 6:
            prox = 4;
            dd = 0x00;
            du = 0x66;
            break; 
            
        case 4:
            prox = 1;
            dd = 0x00;
            du = 0x06;
            break;  
            
        case 1:
           prox = 30;
           dd = 0x4f;
           du = 0x3f;
           break;
        
        default:
            prox = 30;
            dd = 0x4f;
            du = 0x3f;
            break;
    }
    return prox;
}

alt_u8 f_maq_n_3_d(alt_u8 atual){
    alt_u8 prox;
    switch(atual){
        case 29:
            prox = 28;
            dd = 0x5b;
            du = 0x7f;
            break;
            
        case 28:
            prox = 26;
            dd = 0x5b;
            du = 0x7d;
            break;
            
        case 26:
            prox = 25;
            dd = 0x5b;
            du = 0x6d;
            break;
            
        case 25:
            prox = 23;
            dd = 0x5b;
            du = 0x4f;
            break;
            
        case 23:
            prox = 22;
            dd = 0x5b;
            du = 0x5b;
            break; 
            
        case 22:
            prox = 20;
            dd = 0x5b;
            du = 0x3f;
            break;
            
        case 20:
            prox = 19;
            dd = 0x06;
            du = 0x6f;
            break;  
            
        case 19:
            prox = 17;
            dd = 0x06;
            du = 0x07;
            break;
            
        case 17:
            prox = 16;
            dd = 0x06;
            du = 0x7d;
            break;
            
        case 16:
            prox = 14;
            dd = 0x06;
            du = 0x66;
            break;
            
        case 14:
            prox = 13;
            dd = 0x06;
            du = 0x4f;
            break;
            
        case 13:
           prox = 11;
            dd = 0x06;
            du = 0x06;
            break; 
            
        case 11:
            prox = 10;
            dd = 0x06;
            du = 0x3f;
            break;
            
        case 10:
           prox = 8;
            dd = 0x00;
            du = 0x7f;
            break; 
            
        case 8:
           prox = 7;
            dd = 0x00;
            du = 0x07;
            break; 
            
        case 7:
            prox = 5;
            dd = 0x00;
            du = 0x6d;
            break;
            
        case 5:
           prox = 4;
            dd = 0x00;
            du = 0x66;
            break; 
            
        case 4:
           prox = 2;
            dd = 0x00;
            du = 0x5b;
            break;
            
        case 2:
            prox = 1;
            dd = 0x00;
            du = 0x06;
            break;
                        
        case 1:
           prox = 29;
            dd = 0x5b;
            du = 0x6f;
            break;   
            
        default:
            prox = 29;
            dd = 0x5b;
            du = 0x6f;
            break;   
    }
    return prox;
}