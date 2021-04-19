

#include "44b.h"
#include "utils.h"
#include "button.h"
#include "leds.h"
#include "gpio.h"

unsigned int read_button(void)
{
	unsigned int buttons = 0;
	enum digital val;
	//COMPLETAR utilizando el interfaz del puerto G de gpio.h
	//tiene que leer los pines 6 y 7 del puerto G (portG_read) y devolver en la variable buttons
	//un 0 si no hay ningún botón pulsado
	//1 si se a pulsado el botón 1
	//2 si se a pulsado el botón 2

	portG_read(6, &val);
	if (val == LOW)
		//buttons |= 0x1;
		buttons = 1;
	portG_read(7, &val);
	if (val == LOW)
		//buttons |= 0x2;
	buttons = 2;
	return buttons;
}


