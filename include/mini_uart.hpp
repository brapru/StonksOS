#pragma once

class MiniUart
{
	private:
	    void uart_init(void);

	public:
	    MiniUart();
	    char uart_recv(void);
	    void uart_send(char c);
	    void uart_send_string(const char *);
	    void uart_hex(unsigned int);
};

