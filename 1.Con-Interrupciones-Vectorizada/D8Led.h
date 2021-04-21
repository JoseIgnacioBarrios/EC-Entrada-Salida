/*-------------------------------------------------------------------
**
**  Fichero:
**    D8Led.h
**
**
**  Propósito:
**    Contiene las declaraciones de los prototipos de funciones
**    para el acceso al display 8-segmentos de la placa de prototipado
**
** 
**
**-----------------------------------------------------------------*/

#ifndef D8LED_H_
#define D8LED_H_

void D8Led_init(void);
void D8Led_segment(int value); 
void D8Led_digit(int value); 

#endif

