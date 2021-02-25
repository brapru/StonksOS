#include "mini_uart.hpp"
#include "utils.hpp"
#include "peripherals/gpio.hpp"
#include "peripherals/aux.hpp"
#include "stonksos/stdio.hpp"

static Aux s_aux;
static Gpio s_gpio;

MiniUart::MiniUart()
{
	uart_init();
}

void MiniUart::uart_send(char c)
{
	while(1) {
		if(s_aux.get_aux_regs_ptr()->mu_lsr & 0x20) 
			break;
	}
	s_aux.get_aux_regs_ptr()->mu_io = c;
}

char MiniUart::uart_recv(void)
{
	while(1) {
		if(s_aux.get_aux_regs_ptr()->mu_lsr & 0x01) 
			break;
	}
	char c = (char)s_aux.get_aux_regs_ptr()->mu_io & 0xFF;
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

void MiniUart::uart_init(void)
{
	s_gpio.gpio_pin_set_func(TXD, Gpio::GFAlt5);
	s_gpio.gpio_pin_set_func(RXD, Gpio::GFAlt5);

	s_gpio.gpio_pin_enable(TXD);
	s_gpio.gpio_pin_enable(RXD);

	s_aux.get_aux_regs_ptr()->enables = 1;
	s_aux.get_aux_regs_ptr()->mu_control = 0;
        s_aux.get_aux_regs_ptr()->mu_ier = 0xD;
	s_aux.get_aux_regs_ptr()->mu_lcr = 3;
	s_aux.get_aux_regs_ptr()->mu_mcr = 0;

#if RPI_VERSION == 3
	s_aux.get_aux_regs_ptr()->mu_baud_rate = 270;             //Set baud rate to 115200
#endif

#if RPI_VERSION == 4
	s_aux.get_aux_regs_ptr()->mu_baud_rate = 541;             //Set baud rate to 115200
#endif

	s_aux.get_aux_regs_ptr()->mu_control = 3;               //Finally, enable transmitter and receiver

        Stdio::printf("\nValue of mu lcr is: %x\n", s_aux.get_aux_regs_ptr()->mu_lcr);
        Stdio::printf("\nValue of mu mcr is: %x\n", s_aux.get_aux_regs_ptr()->mu_mcr);
        Stdio::printf("\nValue of mu ier is: %x\n", s_aux.get_aux_regs_ptr()->mu_ier);
        Stdio::printf("\nValue of mu iir is: %x\n", s_aux.get_aux_regs_ptr()->mu_iir);
        Stdio::printf("\nValue of mu enables is: %x\n", s_aux.get_aux_regs_ptr()->enables);
        Stdio::printf("\nValue of mu control is: %x\n", s_aux.get_aux_regs_ptr()->mu_control);
        Stdio::printf("\nValue of mu baud is: %x\n", s_aux.get_aux_regs_ptr()->mu_baud_rate);
}

