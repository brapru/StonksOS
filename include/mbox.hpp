#pragma once

#include "types.hpp"
#include "peripherals/base.hpp"

//url reference - https://github.com/bztsrc/raspi3-tutorial/blob/master/04_mailboxes/mbox.c
class Mailbox {
public:
	volatile u32 mbox[36];
	
	const u32 MBOX_REQUEST = 0;

	const u32 VIDEOCORE_MBOX = (PBASE+0x0000B880);
	volatile u32 *MBOX_READ = ((volatile u32*)(VIDEOCORE_MBOX+0x0));
	volatile u32 *MBOX_POLL = ((volatile u32*)(VIDEOCORE_MBOX+0x10));
	volatile u32 *MBOX_SENDER = ((volatile u32*)(VIDEOCORE_MBOX+0x14));
	volatile u32 *MBOX_STATUS = ((volatile u32*)(VIDEOCORE_MBOX+0x18));
	volatile u32 *MBOX_CONFIG = ((volatile u32*)(VIDEOCORE_MBOX+0x1C));
	volatile u32 *MBOX_WRITE = ((volatile u32*)(VIDEOCORE_MBOX+0x20));
	const u32 MBOX_RESPONSE = 0x80000000;
	const u32 MBOX_FULL = 0x80000000;
	const u32 MBOX_EMPTY = 0x40000000;

	const u32 MBOX_CH_POWER = 0;
	const u32 MBOX_CH_FB = 1;
	const u32 MBOX_CH_VUART = 2;
	const u32 MBOX_CH_VCHIQ = 3;
	const u32 MBOX_CH_LEDS = 4;
	const u32 MBOX_CH_BTNS = 5;
	const u32 MBOX_CH_TOUCH = 6;
	const u32 MBOX_CH_COUNT = 7;
	const u32 MBOX_CH_PROP = 8;

	const u32 MBOX_TAG_GETSERIAL = 0x10004;
	const u32 MBOX_TAG_GETMAC = 0x10003;
	const u32 MBOX_TAG_LAST = 0;

	u32 mbox_call(unsigned char);
};
