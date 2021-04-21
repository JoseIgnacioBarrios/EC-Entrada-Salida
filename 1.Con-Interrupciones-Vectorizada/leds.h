/*-------------------------------------------------------------------
**
**  Fichero:
**    leds.h
**
**
**  Propósito:
**    Contiene las definiciones de los prototipos de funciones
**    para el acceso a los leds de la placa de prototipado
**
**  
**
**-----------------------------------------------------------------*/

#ifndef _LEDS_H_
#define _LEDS_H_

void leds_init( void );
void led1_on( void );
void led1_off( void );
void led2_on( void );
void led2_off( void );
void led1_switch( void );
void led2_switch( void );
void leds_switch( void );
void leds_display( unsigned int leds_status );

#endif
