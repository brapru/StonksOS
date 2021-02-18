/* Referenced D13.2.137 from AArch64 Reference Guide */

.globl irq_init_vectors
irq_init_vectors:
	adr x0, vectors
	msr vbar_el1, x0
	ret


/* Referenced C5.2.2 from AArch64 Reference Guide */
.globl irq_enable:
	msr daifclr, #2
	ret

.globl irq_disable:
	msr daifset, #2
	ret
