#pragma once

extern "C" void irq_init_vectors();
extern "C" void irq_enable();
extern "C" void irq_disable();

enum vc_irqs {
	AUX_IRQ = (1 << 29)
};

class IRQ {
private:
	struct IRQRegs_2711 {
		reg32 irq0_pending_0;
		reg32 irq0_pending_1;
		reg32 irq0_pending_2;
		reg32 res0;
		reg32 irq0_enable_0;
		reg32 irq0_enable_1;
		reg32 irq0_enable_2;
		reg32 res1;
		reg32 irq0_disable_0;
		reg32 irq0_disable_1;
		reg32 irq0_disable_2;	
	};
	
	struct IRQRegs_2837 {
		reg32 irq0_pending_0;
		reg32 irq0_pending_1;
		reg32 irq0_pending_2;
		reg32 fiq_control;
		reg32 irq0_enable_1;
		reg32 irq0_enable_2;
		reg32 irq0_enable_0;
		reg32 res;
		reg32 irq0_disable_1;
		reg32 irq0_disable_2;
		reg32 irq0_disable_0;
	};
	
	#if RPI_VERSION == 3
		typedef struct IRQRegs_2837 IRQRegs;
	#endif
	
	#if RPI_VERSION == 4
		typedef struct IRQRegs_2711 IRQRegs;
	#endif	

public:
	IRQ();
	static IRQRegs *get_irq_regs_ptr()
	{
		return reinterpret_cast<IRQRegs *>(PBASE + 0x0000B200);
	}

	static void enable_interrupt_controller(void); 
};
