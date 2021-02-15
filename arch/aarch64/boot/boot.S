#include "mm.hpp"

.section ".text.boot"

.globl _start
_start:
	mrs	x0, mpidr_el1		
	and	x0, x0,#0xFF		// Check processor id
	cbz	x0, master		// Hang for all non-primary CPU
	b	proc_hang

proc_hang:
	wfe 
	b 	proc_hang

master:
	ldr	x0, =_start	

	mrs	x1, CurrentEL
	and	x1, x1, #12

	//running at EL2?
5:	cmp	x1, #4
	beq	5f
	msr	sp_el1, x0
	//enable CNTP for EL1
	mrs	x1, cnthctl_el2
	orr	x1, x1, #3
	msr	cnthctl_el2, x1
	msr	cntvoff_el2, xzr
	//enable AArch64 in EL1
	mov	x1, #(1 << 31)
	orr	x1, x1, #(1 << 1)
	msr	hcr_el2, x1
	mrs	x1, hcr_el2
	//actually change EL to EL1
	mov	x2, #0x3c4
	msr	spsr_el2, x2
	adr	x2, 5f
	msr	elr_el2, x2
	eret

5:	mov 	sp, x0

	adr	x0, __bss_start
	adr	x1, __bss_end
	sub	x1, x1, x0
	bl 	memzero

//	mov	sp, #LOW_MEMORY 
	bl	kernel_main
	b 	proc_hang		// should never come here
