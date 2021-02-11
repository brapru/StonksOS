#include "mini_uart.hpp"
#include "utils.hpp"
#include "peripherals/gpio.hpp"
#include "peripherals/aux.hpp"

MiniUart::MiniUart()
{
	uart_init();
}

void MiniUart::uart_send(char c)
{
	while(1) {
		if(REGS_AUX->mu_lsr & 0x20) 
			break;
	}
	if (c == '\n')
		REGS_AUX->mu_io = '\r';

	REGS_AUX->mu_io = c;
}

char MiniUart::uart_recv(void)
{
	while(1) {
		if(REGS_AUX->mu_lsr & 0x01) 
			break;
	}
	char c = REGS_AUX->mu_io & 0xFF;
	return(c=='\r'?'\n':c);
}

void MiniUart::uart_send_string(const char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send((char)str[i]);
	}
}

void MiniUart::uart_hex(unsigned int d) 
{
	unsigned int n;
	int c;
	for (c = 28; c >= 0; c -=4)
	{
		n = (d >> c)&0xf;
		n += n > 9? 0x37: 0x30;
		uart_send(n);
	}	    
}

#define TXD 14
#define RXD 15

void MiniUart::uart_init(void)
{
	//Gpio *gpio = get_gpio();

	gpio_pin_set_func(TXD, GFAlt5);
	gpio_pin_set_func(RXD, GFAlt5);

	gpio_pin_enable(TXD);
	gpio_pin_enable(RXD);

	REGS_AUX->enables = 1;
	REGS_AUX->mu_control = 0;
        REGS_AUX->mu_ier = 0;
	REGS_AUX->mu_lcr = 3;
	REGS_AUX->mu_mcr = 0;
#if RPI_VERSION == 3
	REGS_AUX->mu_baud_rate = 270;             //Set baud rate to 115200
#endif

#if RPI_VERSION == 4
	REGS_AUX->mu_baud_rate = 541;             //Set baud rate to 115200
#endif

	REGS_AUX->mu_control = 3;               //Finally, enable transmitter and receiver
}
