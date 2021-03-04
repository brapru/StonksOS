#pragma once

#include "peripherals.hpp"
#include "stonksos/stdio.hpp"

#define IRQ_BASE_ADDRESS (PBASE + 0x0000B200)

const char entry_error_messages[16][32] = {
        "SYNC_INVALID_EL1t",
        "IRQ_INVALID_EL1t",
        "FIQ_INVALID_EL1t",
        "ERROR_INVALID_EL1T",

        "SYNC_INVALID_EL1h",
        "IRQ_INVALID_EL1h",
        "FIQ_INVALID_EL1h",
        "ERROR_INVALID_EL1h",

        "SYNC_INVALID_EL0_64",
        "IRQ_INVALID_EL0_64",
        "FIQ_INVALID_EL0_64",
        "ERROR_INVALID_EL0_64",

        "SYNC_INVALID_EL0_32",
        "IRQ_INVALID_EL0_32",
        "FIQ_INVALID_EL0_32",
        "ERROR_INVALID_EL0_32"
};

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

typedef struct IRQRegs_2711 IRQRegs;

class IRQ : public Peripheral<IRQRegs> {
public:
	using Peripheral<IRQRegs>::Peripheral;
		
	static IRQ& instance(){
		static IRQ s_instance(IRQ_BASE_ADDRESS);
		return s_instance;
	}	
	
	IRQ(IRQ const&) 	   = delete;
	void operator=(IRQ const&) = delete;

	static void initialize(void);
	
	void enable_interrupt_controller(void); 
	void init_vectors(void);
	void irq_enable(void);
	void irq_disable(void);

private:
	IRQ(PhysicalAddress address = IRQ_BASE_ADDRESS)
	: Peripheral(address)
	{
	}
	
};
