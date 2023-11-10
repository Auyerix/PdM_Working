#include <stdint.h>
#include <stdbool.h>


typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;


void debounceFSM_init(void);		// debe cargar el estado inicial
void debounceFSM_update(void);	// debe leer las entradas, resolver la lógica de
							// transición de estados y actualizar las salidas
void buttonPressed(void);			// debe encender el LED
void buttonReleased(void);		// debe apagar el LED

/* La función readKey debe leer una variable interna del módulo y devolver true o false si la tecla fue presionada.
 * Si devuelve true, debe resetear (poner en false) el estado de la variable.*/
bool_t readKey(void);

