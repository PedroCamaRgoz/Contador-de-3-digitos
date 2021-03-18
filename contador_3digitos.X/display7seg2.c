/*
 * File:   display7seg2.c
 * Author: Pedro
 *
 * Created on 11 de Março de 2021, 21:27
 */


#include <xc.h>
#include "config.h"
#include "delay.h"

#define QTD_DIGITOS         3  // unidade,dezena e centena 
#define BASE                10

#define DISP7SEG_BUS( x )   PORTB = x
#define HAB_DEZENA( x )     PORTDbits.RD6 = x
#define HAB_UNIDADE( x )    PORTDbits.RD5 = x
#define HAB_CENTENA( x )    PORTDbits.RD7 = x


char digitos7seg[16] = {    0x3F, 0x06, 0x5B, 0x4F, 
                            0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F, 0x77, 0x7C, 
                            0x39, 0x5E, 0x79, 0x71  };

void disp7segX2_init( void )
{
    ANSELH = 0;  // desabilita as portas analogicas do PORTB;
    TRISB = 0x00;
    TRISDbits.TRISD7 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD5 = 0;
    
    
    HAB_DEZENA ( 1 );
    HAB_UNIDADE( 1 );
    HAB_CENTENA( 1 );
    
    DISP7SEG_BUS(0xFF);    delay(500);
    DISP7SEG_BUS(0x00);    delay(500);
    DISP7SEG_BUS(0xFF);    delay(500);
    DISP7SEG_BUS(0x00);    delay(500);
}

unsigned char posicao = 0;                              // inicia o switch como 0, "case:0"
void disp7segX2( unsigned char num )
{
    switch( posicao )
    {
        case 0: // Unidade
                HAB_DEZENA ( 0 );
                HAB_CENTENA( 0 );
                DISP7SEG_BUS( digitos7seg[num % BASE] ); // EX: 1%10 = 1 na casa da unidade
                HAB_UNIDADE( 1 );
                break;

        case 1: // Dezena
                HAB_UNIDADE( 0 );
                HAB_CENTENA( 0 );
                DISP7SEG_BUS( digitos7seg[(num / BASE) % BASE] ); // EX : (10/10)%10 = 1 na casa da dezena
                HAB_DEZENA( 1 );
                break;
                
                
        case 2: // CENTENA
                HAB_UNIDADE( 0 );
                HAB_DEZENA ( 0 );
                DISP7SEG_BUS( digitos7seg[((num / BASE)/BASE) % BASE] ); // EX: ((100/10)/10)%10 = 1 na casa da centena
                HAB_CENTENA( 1 );
                break;
                
    }
    posicao = ++posicao % QTD_DIGITOS; // formula para o switch ir de case 0 a case 2 até o fim da contagem estabelecida;
}
  

