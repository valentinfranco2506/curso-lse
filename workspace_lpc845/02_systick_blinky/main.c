#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_swm.h"
#include "fsl_power.h"
#include "fsl_adc.h"

#define LED_BLUE, GPIO, 1,  // Pin para el LED azul
#define LED_D1, GPIO, 0,   // Pin para el LED D1
/**
 * @brief Programa principal
 */
int main(void) {

	// Inicializacion
	BOARD_BootClockFRO24M();

    // Estructura de configuracion de salida
    gpio_pin_config_t out_config = { kGPIO_DigitalOutput, 1 };

    // Habilito el puerto 1
    GPIO_PortInit(GPIO, 1);
    GPIO_PortInit(GPIO, 0);
    // Configuro LED como salida
     GPIO_PinInit(GPIO, 1, LED_BLUE, &out_config);
     GPIO_PinInit(GPIO, 0, LED_D1, &out_config);

    // Configuro SysTick para 1 ms
    SysTick_Config(SystemCoreClock / 1000);

    while(1);
    return 0 ;
}

void SysTick_Handler(void) {
	// Variable para contar interrupciones
	static uint16_t i = 0;
    static uint16_t a = 0;

	// Incremento contador
	i++;
    a++;
	// Verifico si el SysTick se disparo 500 veces (medio segundo)
	if(i == 500) {
		// Reinicio el contador
		i = 0;
		// Conmuto el LED
		GPIO_PinWrite(LED_BLUE, !GPIO_PinRead(GPIO, 1, LED_BLUE));
	}

    if(a == 1500) {
		// Reinicio el contador
		a = 0;
		// Conmuto el LED
		GPIO_PinWrite(LED_D1, !GPIO_PinRead(GPIO, 0, LED_D1));
}
}