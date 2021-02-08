#include "mini_uart.hpp"
#include "mbox.hpp"

/*  StonksOS kernel entry point */
extern "C" [[noreturn]] void kernel_main(){
	
	MiniUart mu;
	mu.uart_send_string("\r\nWelcome to StonksOS.\r\n");

	mbox[0] = 8*4;			//length of message
	mbox[1] = MBOX_REQUEST;		//this is a request message

	mbox[2] = MBOX_TAG_GETSERIAL;	//getserialnumber command
	mbox[3] = 8;			//buffer size
	mbox[4] = 8;			
	mbox[5] = 0;			//clear output buffer
	mbox[6] = 0;

	mbox[7] = MBOX_TAG_LAST;

	//send message to GPU and receive answer
	if (mbox_call(MBOX_CH_PROP)) 
	{
		mu.uart_send_string("My serial number is: ");
		mu.uart_hex(mbox[6]);
		mu.uart_hex(mbox[5]);
		mu.uart_send('\n');
	}
	else
	{
		mu.uart_send_string("unable to query serial!\n");
	}

	while(1){
		mu.uart_send(mu.uart_recv());
	}
}
