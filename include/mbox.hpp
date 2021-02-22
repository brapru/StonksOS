#pragma once

#include "types.hpp"
#include "peripherals/base.hpp"

//url reference - https://github.com/bztsrc/raspi3-tutorial/blob/master/04_mailboxes/mbox.c
class Mailbox {
public:
	volatile u32 __attribute__((aligned(16))) mbox[36];

	enum {
		MBOX_REQUEST = 0
	};

	enum {
		MBOX_CH_POWER = 0,
		MBOX_CH_FB = 1,
		MBOX_CH_VUART = 2,
		MBOX_CH_VCHIQ = 3,
		MBOX_CH_LEDS = 4,
		MBOX_CH_BTNS = 5,
		MBOX_CH_TOUCH = 6,
		MBOX_CH_COUNT = 7,
        	MBOX_CH_PROP = 8
	};
	
	enum {
		MBOX_TAG_GETSERIAL = 0x10004,
		MBOX_TAG_GETMAC = 0x10003,

		MBOX_TAG_SETPOWER   = 0x28001,
		MBOX_TAG_SETCLKRATE = 0x38002,

		MBOX_TAG_SETPHYWH   = 0x48003,
		MBOX_TAG_SETVIRTWH  = 0x48004,
		MBOX_TAG_SETVIRTOFF = 0x48009,
		MBOX_TAG_SETDEPTH   = 0x48005,
		MBOX_TAG_SETPXLORDR = 0x48006,
		MBOX_TAG_GETFB      = 0x40001,
		MBOX_TAG_GETPITCH   = 0x40008,

		MBOX_TAG_LAST = 0
	};

	u32 mbox_call(unsigned char);
	static void mbox_get_mac();
};
