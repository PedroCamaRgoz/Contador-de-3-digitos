/*
 * File:   main.c
 * Author: Pedro
 *
 * Created on 8 de Março de 2021, 20:38
 */

#include <xc.h>
#include "config.h"
#include "delay.h"
#include "display7seg2.h" /


void main(void)                      // void esquerda = (nao recebe/le ou retorna)                                                                                    
{                                    // main =(nome reservado para função principal) 
    char num = 0;                    // void direita  =(nao devolve dado/parametro)
    int nScan = 0;
    disp7segX2_init();
    
    while( 1 )
    {
       disp7segX2( num );
        
       if( ++nScan > 200 )           // *processo :  
       {                             // conta 200 milissegundos > faz o comando e zera a contagem > Repete o *processo
            nScan = 0;
            num = ++num % 1000;      // *processo : 
                                     // "num" ira soma 1 a cada contagem de 200 milissegundos > quando "num" for igual a 999>
                                     // > "num" zera > Repete o *processo
        }
        
       delay(1);                     // cada vez que chegar aqui adiciona +1 no nScan até dar 200 milissegundos
    }
    return;
}