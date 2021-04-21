/*-----------------------------------------------------------------
**
**  Fichero:
**    button.c
**
**
**  Prop�sito:
**    Contiene las definiciones de los prototipos de funciones
**    para la gesti�n de los pulsadores de la placa de prototipado
**
**  Notas de dise�o:
**
**---------------------------------------------------------------*/

#ifndef BUTTON_H_
#define BUTTON_H_

#define BUT1 0x1
#define BUT2 0x2

unsigned int read_button(void);

#endif /* BUTTON_H_ */
