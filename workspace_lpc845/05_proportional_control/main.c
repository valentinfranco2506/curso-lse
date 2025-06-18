
/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "peripherals.h"
#include "board.h"
#include "fsl_power.h"
#include "fsl_adc.h"
#include "fsl_debug_console.h"
#include "fsl_swm.h"
#include "app.h"

//defino el pote 21
#define RV21, GPIO, 0, 7
//defino el pote 22
#define RV22, GPIO, 0, 18
// Canal del ADC para el potenciometro
#define REF_POT_CH	8

int main(void)
{
    GPIO_PortInit(GPIO , 0);
    gpio_pin_config_t input = { kGPIO_DigitalInput };
    GPIO_PinInit(GPIO, 0, USR_BTN, &input);
    // Activo clock de matriz de conmutacion
    CLOCK_EnableClock(kCLOCK_Swm);
    // Configuro la funcion de ADC en el canal del RV21 y RV22
    SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN0, true);
    SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN8, true);
    // Desactivo clock de matriz de conmutacion
    CLOCK_DisableClock(kCLOCK_Swm);

    // Elijo clock desde el FRO con divisor de 1 (30MHz)
    CLOCK_Select(kADC_Clk_From_Fro);
    CLOCK_SetClkDivider(kCLOCK_DivAdcClk, 1);

    // Prendo el ADC
    POWEzR_DisablePD(kPDRUNCFG_PD_ADC0);

    // Obtengo frecuencia deseada y calibro ADC
	uint32_t frequency = CLOCK_GetFreq(kCLOCK_Fro) / CLOCK_GetClkDivider(kCLOCK_DivAdcClk);
	ADC_DoSelfCalibration(ADC0, frequency);
	// Configuracion por defecto del ADC
	adc_config_t adc_config;
	ADC_GetDefaultConfig(&adc_config);
    // Habilito el ADC
	ADC_Init(ADC0, &adc_config);
	// Configuracion para la conversion para secuencia A
	adc_conv_seq_config_t adc_sequence = {
		.channelMask = 1 << RV21,								// Canal del RV21
		.triggerMask = 0,										// No hay trigger por hardware
		.triggerPolarity = kADC_TriggerPolarityPositiveEdge,	// Flanco ascendente
		.enableSyncBypass = false,								// Sin bypass de trigger
		.interruptMode = kADC_InterruptForEachConversion		// Interrupciones para cada conversion
	};
	ADC_SetConvSeqAConfig(ADC0, &adc_sequence);
	// Conversion para secuencia B
	adc_sequence.channelMask = 1 << RV22;		// Canal del RV22
	ADC_SetConvSeqBConfig(ADC0, &adc_sequence);
	// Habilito secuencias
	ADC_EnableConvSeqA(ADC0, true);
	ADC_EnableConvSeqB(ADC0, true);

	// Elimino tarea
	vTaskDelete(NULL);
}
GPIO_PinInit(GPIO, 0, USR_BTN, &input); // Inicializa el puerto GPIO 0
    /* Init board hardware. */
    BOARD_InitHardware();

    /* Add user custom codes below */
    while (1)
    {
    }
}
