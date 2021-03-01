#pragma once

#include "peripherals.hpp"

#define IRQ_BASE_ADDRESS (PBASE + 0x0000B200)

enum vc_irqs {
	AUX_IRQ = (1 << 29)
};

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

class IRQ {
public:
	IRQ(PhysicalAddress address = IRQ_BASE_ADDRESS)
	: m_peripheral(address) 
	{
	}
	
	static void initialize(void);
	
	void init_vectors(void);
	void enable_interrupt_controller(void); 
	void irq_enable(void);
	void irq_disable(void);

	IRQRegs* get_regmap_ptr(void);	

private:
	Peripheral<IRQRegs> m_peripheral;
};
