#pragma once
#include "peripherals/aux.hpp"

class MiniUart
{
	private:
	    Aux aux;

	    void uart_init(void);

	public:
	    MiniUart();
	    
	    Aux *get_aux(void);
	    char uart_recv(void);
	    void uart_send(char c);
	    void uart_send_string(const char *);
	    void uart_hex(unsigned int);
};

