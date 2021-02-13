#pragma once

#include "types.hpp"
#include "peripherals/aux.hpp"
#include "peripherals/gpio.hpp"

class MiniUart
{
	private:
	    Aux aux;

	    void uart_init(void);

	public:
	    MiniUart();
	    
	    Aux *get_aux() { return &aux; }
	    char uart_recv(void);
	    void uart_send(char c);
	    void uart_send_string(const char *);
	    void uart_hex(unsigned int);
};

