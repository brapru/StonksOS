#pragma once

#include "types.hpp"
#include "peripherals/aux.hpp"
#include "peripherals/gpio.hpp"

class MiniUart
{
	private:
	    Aux aux;
	    Gpio gpio;

	    void uart_init(void);

	public:
	    MiniUart();
	    
	    Aux *get_aux_object() { return &aux; }
	    Gpio *get_gpio_object() { return &gpio; }
	    char uart_recv(void);
	    void uart_send(char c);
	    void uart_send_string(const char *);
	    void uart_hex(unsigned int);
};

