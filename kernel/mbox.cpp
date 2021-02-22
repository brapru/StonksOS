#include "stonksos/stdio.hpp"
#include "mbox.hpp"
#include "types.hpp"
#include "peripherals/base.hpp"
#include "utils.hpp"

static Mailbox s_mbox;

//mailbox message buffer
volatile u32 __attribute__((aligned(16))) mbox[36];

enum {
	VIDEOCORE_MBOX = (PBASE + 0x0000B880),
	MBOX_READ      = (VIDEOCORE_MBOX + 0x0),
	MBOX_POLL      = (VIDEOCORE_MBOX + 0x10),
	MBOX_SENDER    = (VIDEOCORE_MBOX + 0x14),
	MBOX_STATUS    = (VIDEOCORE_MBOX + 0x18),
	MBOX_CONFIG    = (VIDEOCORE_MBOX + 0x1C),
	MBOX_WRITE     = (VIDEOCORE_MBOX + 0x20),
	MBOX_RESPONSE  = 0x80000000,
	MBOX_FULL      = 0x80000000,
	MBOX_EMPTY     = 0x40000000
};

u32 Mailbox::mbox_call(unsigned char ch)
{
	u32 r = ((u32)((i64) &mbox) & ~0xf) | (ch & 0xf);

	//wait until we can write to the mailbox
	while (kernel::mmio_read(MBOX_STATUS) & MBOX_FULL);

	//write address of our message to mailbox with channel identifier
	kernel::mmio_write(MBOX_WRITE, r);

	//wait for the response
	while(1) 
	{
		//is there a response?
		while (kernel::mmio_read(MBOX_STATUS) & MBOX_EMPTY);
		
		//is it a response to our message?
		if (r == kernel::mmio_read(MBOX_READ))
			//is it a valid successful response?
			return mbox[1]==MBOX_RESPONSE;
	}
	return 0;
}

void Mailbox::mbox_get_mac()
{
	s_mbox.mbox[0] = 8*4;
	s_mbox.mbox[1] = s_mbox.MBOX_REQUEST;
	s_mbox.mbox[2] = s_mbox.MBOX_TAG_GETMAC;
	s_mbox.mbox[3] = 8;
	s_mbox.mbox[4] = 8;
	s_mbox.mbox[5] = 0;
	s_mbox.mbox[6] = 0;
	s_mbox.mbox[7] = s_mbox.MBOX_TAG_LAST;

	if (s_mbox.mbox_call(s_mbox.MBOX_CH_PROP)) {
		Stdio::printf("My HW MAC is: %#010x %#010x\n", s_mbox.mbox[6], s_mbox.mbox[5]);
	}
	else
	    Stdio::puts("unable to query MAC");
}

