#include "mbox.hpp"
#include "types.hpp"

//mailbox message buffer
volatile u32 __attribute__((aligned(16))) mbox[36];

u32 Mailbox::mbox_call(unsigned char ch)
{
	u32 r = (((u32)((unsigned long)&mbox)&~0xf) | (ch&0xf));

	//wait until we can write to the mailbox
	do {asm volatile("nop");}while(*MBOX_STATUS & MBOX_FULL);

	//write address of our message to mailbox with channel identifier
	*MBOX_WRITE = r;

	//wait for the response
	while(1) 
	{
		//is there a response?
		do{asm volatile("nop");}while(*MBOX_STATUS & MBOX_EMPTY);
		//is it a response to our message?
		if (r == *MBOX_READ)
			//is it a valid successful response?
			return mbox[1]==MBOX_RESPONSE;
	}
	return 0;
}



