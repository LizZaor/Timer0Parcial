#include <18F4620.h>
#include <stdio.h>
#include <stdlib.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#USE DELAY (clock=40000000)
int flagserial=0;
#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O

#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #define RX_232        PIN_C7
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1,UART1,RCV=RX_232)
   #use fast_io(c)
#endif 

char CaracterRecibido;
int contador=0;

int aux=0;
#int_rda
void isr_rda(void){
    CaracterRecibido=getc();
    flagserial=0;
}

#int_timer0
void timer_0()
{ 
    set_timer0(15536);
    contador++;
}
void main(void) {
    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_2);
    set_timer0(1934464);
    enable_interrupts(int_timer0);
    enable_interrupts(global);
    output_a(0x0);   
    output_b(0x0);    
    output_d(0x0);
    int16 conteo;
    while (TRUE) {
    
    if(flagserial==0){
    CaracterRecibido;
    
    if(CaracterRecibido=="x"|| CaracterRecibido=="X"){
    aux++;
       if(aux==1){//puerto A
       for(conteo=64;conteo>=1;conteo/=2)
        {
            output_a(conteo);
            delay_ms(500);
        }
       }else if(aux==2){//puerto B
       for(conteo=128;conteo>=1;conteo/=2)
        {
            output_b(conteo);
            delay_ms(500);
        }
       }else if(aux==3){//puerto C
       for(conteo=128;conteo>=1;conteo/=2)
        {
            output_d(conteo);
            delay_ms(500);
        }
       aux=0;
       }       
    }
    
    
    if(CaracterRecibido=="y"|| CaracterRecibido=="Y"){
    aux++;
       if(aux==1){//puerto A
       for(conteo=64;conteo>=1;conteo/=2)
        {
            output_d(conteo);
            delay_ms(500);
        }
       }else if(aux==2){//puerto B
       for(conteo=128;conteo>=1;conteo/=2)
        {
            output_b(conteo);
            delay_ms(500);
        }
       }else if(aux==3){//puerto C
       for(conteo=128;conteo>=1;conteo/=2)
        {
            output_a(conteo);
            delay_ms(500);
        }
       aux=0;
       }       
    }
    
    if(CaracterRecibido=="i"|| CaracterRecibido=="I"){
         for(conteo=128;conteo>=1;conteo/=2)
        {
            output_b(conteo);
            delay_ms(500);
        }
    }
    
    
    if(CaracterRecibido=="d"|| CaracterRecibido=="D"){
         for(conteo=1;conteo<=128;conteo*=2)
        {
            output_d(conteo);
            delay_ms(500);
        }
      }
    }
  }
}
