#include "utils.hpp"
#include "peripherals/mini_uart.hpp"
#include "peripherals/gpio.hpp"

void uart_send(char c)
{
	while(1) {
		if(kernel::get32(AUX_MU_LSR_REG)&0x20) 
			break;
	}
	if (c == '\n')
		kernel::put32(AUX_MU_IO_REG, '\r');

	kernel::put32(AUX_MU_IO_REG,c);
}

char uart_recv(void)
{
	while(1) {
		if(kernel::get32(AUX_MU_LSR_REG)&0x01) 
			break;
	}
	char c = kernel::get32(AUX_MU_IO_REG)&0xFF;
	return(c=='\r'?'\n':c);
}

void uart_send_string(const char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send((char)str[i]);
	}
}

void uart_hex(unsigned int d) 
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

void uart_init(void)
{
	unsigned int selector;

	selector = kernel::get32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 2<<12;                      // set alt5 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 2<<15;                      // set alt5 for gpio15
	kernel::put32(GPFSEL1,selector);

	kernel::put32(GPPUD,0);
	kernel::delay(150);
	kernel::put32(GPPUDCLK0,(1<<14)|(1<<15));
	kernel::delay(150);
	kernel::put32(GPPUDCLK0,0);

	kernel::put32(AUX_ENABLES,1);                   //Enable mini uart (this also enables access to its registers)
	kernel::put32(AUX_MU_CNTL_REG,0);               //Disable auto flow control and disable receiver and transmitter (for now)
	kernel::put32(AUX_MU_IER_REG,0);                //Disable receive and transmit interrupts
	kernel::put32(AUX_MU_LCR_REG,3);                //Enable 8 bit mode
	kernel::put32(AUX_MU_MCR_REG,0);                //Set RTS line to be always high
	
#if RPI_VERSION == 3
	kernel::put32(AUX_MU_BAUD_REG,270);             //Set baud rate to 115200
#endif

#if RPI_VERSION == 4
	kernel::put32(AUX_MU_BAUD_REG,541);             //Set baud rate to 115200
#endif

	kernel::put32(AUX_MU_CNTL_REG,3);               //Finally, enable transmitter and receiver
}
