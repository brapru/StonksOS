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
		if(g_aux.get_aux_regs_ptr()->mu_lsr & 0x20) 
			break;
	}
	g_aux.get_aux_regs_ptr()->mu_io = c;
}

char MiniUart::uart_recv(void)
{
	while(1) {
		if(g_aux.get_aux_regs_ptr()->mu_lsr & 0x01) 
			break;
	}
	char c = (char)g_aux.get_aux_regs_ptr()->mu_io & 0xFF;
	return(c=='\r'?'\n':c);
}

void MiniUart::uart_send_string(const char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send(str[i]);
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

MiniUart g_miniuart;
void MiniUart::uart_init(void)
{

	g_gpio.gpio_pin_set_func(TXD, Gpio::GFAlt5);
	g_gpio.gpio_pin_set_func(RXD, Gpio::GFAlt5);

	g_gpio.gpio_pin_enable(TXD);
	g_gpio.gpio_pin_enable(RXD);

	g_aux.get_aux_regs_ptr()->enables = 1;
	g_aux.get_aux_regs_ptr()->mu_control = 0;
        g_aux.get_aux_regs_ptr()->mu_ier = 0;
	g_aux.get_aux_regs_ptr()->mu_lcr = 3;
	g_aux.get_aux_regs_ptr()->mu_mcr = 0;
#if RPI_VERSION == 3
	g_aux.get_aux_regs_ptr()->mu_baud_rate = 270;             //Set baud rate to 115200
#endif

#if RPI_VERSION == 4
	g_aux.get_aux_regs_ptr()->mu_baud_rate = 541;             //Set baud rate to 115200
#endif

	g_aux.get_aux_regs_ptr()->mu_control = 3;               //Finally, enable transmitter and receiver
	//uart_send('\r');
	//uart_send('\n');
	//uart_send('\n');
}
