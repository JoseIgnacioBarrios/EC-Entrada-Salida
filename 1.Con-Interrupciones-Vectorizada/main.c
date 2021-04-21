#include <stdio.h>
#include "44b.h"
#include "leds.h"
#include "utils.h"
#include "D8Led.h"
#include "intcontroller.h"
#include "timer.h"
#include "gpio.h"


struct RLstat {
	int moving;
	int speed;
	int direction;
	int position;
	int contbutton;
};

static struct RLstat RL = {
	.moving = 0,
	.speed = 5,
	.direction = 0,
	.position = 0,
	.contbutton=0,
};

void timer_ISR(void) __attribute__ ((interrupt ("IRQ")));
void button_ISR(void) __attribute__ ((interrupt ("IRQ")));

void timer_ISR(void)
{
	//COMPLETAR: tomar el código de avance de posición del led rotante de la práctica anterior
	if (RL.direction) {
						RL.position++;
						if (RL.position > 5)
							RL.position = 0;
					} else {
						RL.position--;
						if (RL.position < 0)
							RL.position = 5;
					}

					//D8Led_segment(RL.position);
					//RL.iter = RL.speed;
	D8Led_segment(RL.position);
	ic_cleanflag(INT_TIMER0);
}

void button_ISR(void)
{
	unsigned int whicheint = rEXTINTPND;
	unsigned int buttons = (whicheint >> 2) & 0x3;

	//COMPLETAR: usar el código de la primera parte parte de atención a los
	//pulsadores
	if(buttons & 0x1){
		led1_off();
				led2_off();
				if (RL.direction){
					tmr_update(TIMER0);
					tmr_start(TIMER0);
					RL.direction = 0;
				}
				else{
					tmr_update(TIMER0);
					tmr_start(TIMER0);
					RL.direction = 1;
					//RL.iter = RL.speed;
				}

	}
	if(buttons & 0x2){
				RL.contbutton=RL.contbutton+1;
				if(RL.contbutton%2){
					led2_switch();
				}
				else {
					led1_switch();
				}
				if (RL.moving) {
					tmr_stop(TIMER0);
					RL.moving = 0;
				} else {
					tmr_update(TIMER0);
					tmr_start(TIMER0);
					RL.moving = 1;
				}
	}
	// eliminamos rebotes
	Delay(2000);
	// borramos el flag en extintpnd

	rEXTINTPND |= (buttons<<2);  //COMPLETAR: debemos borrar las peticiones de interrupción en
		         //EXTINTPND escribiendo un 1 en los flags que queremos borrar (los
				 //correspondientes a los pulsadores pulsados)
	ic_cleanflag(INT_EINT4567); //borramos el flag de interrupcion correspondiente a la linea EINT4567
}



int setup(void)
{
	leds_init();
	D8Led_init();
	D8Led_segment(RL.position);

	/* Port G: configuración para generación de interrupciones externas,
	 *         botones y teclado
	 **/

	//COMPLETAR: utilizando el interfaz para el puerto G definido en gpio.h
	//configurar los pines 1, 6 y 7 del puerto G para poder generar interrupciones
	//externas por flanco de bajada por ellos y activar las correspondientes
	//resistencias de pull-up.
	portG_conf(6,EINT);
	portG_eint_trig(6,FALLING);
	portG_conf_pup(6,ENABLE);
	portG_conf(7,EINT);
	portG_eint_trig(7,FALLING);
	portG_conf_pup(7,ENABLE);
	portG_conf(1,EINT);
	portG_eint_trig(1,FALLING);
	portG_conf_pup(1,ENABLE);
	/********************************************************************/

	/* Configuración del timer */

	//COMPLETAR: tomar el código de la segunda parte

	tmr_set_prescaler(0, 255);
	tmr_set_divider(0, D1_8);
	tmr_set_count(TIMER0, 62500, 31250);
	tmr_update(TIMER0);
	tmr_set_mode(TIMER0, RELOAD);
	tmr_stop(TIMER0);

	if (RL.moving)
		tmr_start(TIMER0);
	/***************************/

	// Registramos las ISRs
	pISR_TIMER0   = (unsigned) timer_ISR;
	pISR_EINT4567 = (unsigned) button_ISR;
	

	/* Configuración del controlador de interrupciones
	 * Habilitamos la línea IRQ, en modo vectorizado 
	 * Configuramos el timer 0 en modo IRQ y habilitamos esta línea
	 * Configuramos la línea EINT4567 en modo IRQ y la habilitamos*/

	ic_init();
	//COMPLETAR: utilizando el interfaz definido en intcontroller.h
	//		habilitar la línea IRQ en modo vectorizado
	//		deshabilitar la línea FIQ
	//		configurar la línea INT_TIMER0 en modo IRQ
	//		configurar la línea INT_EINT4567 en modo IRQ
	//		habilitar la línea INT_TIMER0
	//		habilitar la línea INT_EINT4567
	
	ic_conf_irq(ENABLE, VEC);
	ic_conf_fiq(DISABLE);
	ic_conf_line(INT_TIMER0, IRQ);
	ic_conf_line(INT_EINT4567,IRQ);
	ic_enable(INT_TIMER0);
	ic_enable(INT_EINT4567);
	/***************************************************/

	Delay(0);
	return 0;
}

int loop(void)
{
	return 0;
}


int main(void)
{
	setup();

	while (1) {
		loop();
	}
}
