#include "gpio_simple.h"

GPIO_RESULT 	gpio_setup(const portpin pin, GPIO_MODE mode )
{

	ADI_GPIO_PORT port = (ADI_GPIO_PORT) ((pin >> 16) & 0xF);
	uint16_t pinNumber = (pin & 0x001F);
	uint32_t pinMask = (uint32_t) (1 << pinNumber);

	volatile uint32_t * pREG_PORT_DIR_SET, * pREG_PORT_DIR_CLR;

	switch (port) {
		case ADI_GPIO_PORT_A:
			pREG_PORT_DIR_SET = pREG_PORTA_DIR_SET;
			pREG_PORT_DIR_CLR = pREG_PORTA_DIR_CLR;
			break;
		case ADI_GPIO_PORT_B:
			pREG_PORT_DIR_SET = pREG_PORTB_DIR_SET;
			pREG_PORT_DIR_CLR = pREG_PORTB_DIR_CLR;
			break;
		case ADI_GPIO_PORT_C:
			pREG_PORT_DIR_SET = pREG_PORTC_DIR_SET;
			pREG_PORT_DIR_CLR = pREG_PORTC_DIR_CLR;
			break;
		case ADI_GPIO_PORT_D:
			pREG_PORT_DIR_SET = pREG_PORTD_DIR_SET;
			pREG_PORT_DIR_CLR = pREG_PORTD_DIR_CLR;
			break;
		case ADI_GPIO_PORT_E:
			pREG_PORT_DIR_SET = pREG_PORTE_DIR_SET;
			pREG_PORT_DIR_CLR = pREG_PORTE_DIR_CLR;
			break;
		case ADI_GPIO_PORT_F:
			pREG_PORT_DIR_SET = pREG_PORTF_DIR_SET;
			pREG_PORT_DIR_CLR = pREG_PORTF_DIR_CLR;
			break;
		case ADI_GPIO_PORT_G:
			pREG_PORT_DIR_SET = pREG_PORTG_DIR_SET;
			pREG_PORT_DIR_CLR = pREG_PORTG_DIR_CLR;
			break;
		default:
			return GPIO_FAILURE;

	}

    if (mode == GPIO_OUTPUT) {
    	*pREG_PORT_DIR_SET = pinMask;
    }
    else if (mode == GPIO_INPUT) {
 		*pREG_PORT_DIR_CLR = pinMask;
 	} else {
 		return GPIO_FAILURE;
 	}

 	return GPIO_SUCCESS;

}

GPIO_RESULT 	gpio_write(const portpin pin, GPIO_VAL value ) {

    ADI_GPIO_PORT port = (ADI_GPIO_PORT) ((pin >> 16) & 0xF);
    uint16_t pinNumber = (pin & 0x001F);
    uint32_t pinMask = (uint32_t) (1 << pinNumber);

    volatile uint32_t * pREG_PORT_DATA_SET, * pREG_PORT_DATA_CLR;

    switch (port) {
        case ADI_GPIO_PORT_A:
            pREG_PORT_DATA_SET = pREG_PORTA_DATA_SET;
            pREG_PORT_DATA_CLR = pREG_PORTA_DATA_CLR;
            break;
        case ADI_GPIO_PORT_B:
            pREG_PORT_DATA_SET = pREG_PORTB_DATA_SET;
            pREG_PORT_DATA_CLR = pREG_PORTB_DATA_CLR;
            break;
        case ADI_GPIO_PORT_C:
            pREG_PORT_DATA_SET = pREG_PORTC_DATA_SET;
            pREG_PORT_DATA_CLR = pREG_PORTC_DATA_CLR;
            break;
        case ADI_GPIO_PORT_D:
            pREG_PORT_DATA_SET = pREG_PORTD_DATA_SET;
            pREG_PORT_DATA_CLR = pREG_PORTD_DATA_CLR;
            break;
        case ADI_GPIO_PORT_E:
            pREG_PORT_DATA_SET = pREG_PORTE_DATA_SET;
            pREG_PORT_DATA_CLR = pREG_PORTE_DATA_CLR;
            break;
        case ADI_GPIO_PORT_F:
            pREG_PORT_DATA_SET = pREG_PORTF_DATA_SET;
            pREG_PORT_DATA_CLR = pREG_PORTF_DATA_CLR;
            break;
        case ADI_GPIO_PORT_G:
            pREG_PORT_DATA_SET = pREG_PORTG_DATA_SET;
            pREG_PORT_DATA_CLR = pREG_PORTG_DATA_CLR;
            break;
        default:
        	return GPIO_FAILURE;
    }

    if (value == GPIO_HIGH) {
    	*pREG_PORT_DATA_SET = pinMask;
    }
    else if (value == GPIO_LOW) {
    	*pREG_PORT_DATA_CLR = pinMask;
    }
    else {
    	return GPIO_FAILURE;
    }

    return GPIO_SUCCESS;
}


GPIO_VAL	gpio_read(const portpin pin )
{

    ADI_GPIO_PORT port = (ADI_GPIO_PORT) ((pin >> 16) & 0xF);
    uint16_t pinNumber = (pin & 0x001F);
    uint32_t pinMask = (uint32_t) (1 << pinNumber);

    volatile uint32_t * pREG_PORT_DATA;

    switch (port) {
        case ADI_GPIO_PORT_A:   pREG_PORT_DATA = pREG_PORTA_DATA; break;
        case ADI_GPIO_PORT_B:   pREG_PORT_DATA = pREG_PORTB_DATA; break;
        case ADI_GPIO_PORT_C:   pREG_PORT_DATA = pREG_PORTC_DATA; break;
        case ADI_GPIO_PORT_D:   pREG_PORT_DATA = pREG_PORTD_DATA; break;
        case ADI_GPIO_PORT_E:   pREG_PORT_DATA = pREG_PORTE_DATA; break;
        case ADI_GPIO_PORT_F:   pREG_PORT_DATA = pREG_PORTF_DATA; break;
        case ADI_GPIO_PORT_G:   pREG_PORT_DATA = pREG_PORTG_DATA; break;
        default:    break; 
    }

    if (*pREG_PORT_DATA & pinMask) return GPIO_HIGH;
    else return GPIO_LOW;

}
