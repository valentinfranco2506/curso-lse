#include "board.h"
//hola
#define Led_BLUE  GPIO 1, 1
#define delay(t)  for (uint32_t i = 0; i < t; i++)


int main(void){
    //Incializo puerto 1
    GPIO_PortInit(GPIO, 1);
    //Inicializo pin como salida
    gpio_pin_config_t out_config = {.pinDirection = kGPIO_DigitalOutput, .outputLogic = 1};
    GPIO_PinInit(Led_BLUE, &out_config);

    while(1){

        GPIO_PinWrite(Led_BLUE, !GPIO_PinRead(Led_BLUE));
        for(uint32_t i = 0; i < 50000; i++);
    }
    return 0;
}