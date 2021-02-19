#pragma once

#include "types.hpp"
#include "peripherals/base.hpp"

class Aux {
private:
    struct AuxRegs {
	reg32 irq_status;
	reg32 enables;
	reg32 reserved[14];
	reg32 mu_io;
	reg32 mu_ier;
	reg32 mu_iir;
	reg32 mu_lcr;
	reg32 mu_mcr;
	reg32 mu_lsr;
	reg32 mu_msr;
	reg32 mu_scratch;
	reg32 mu_control;
	reg32 mu_status;
	reg32 mu_baud_rate;
    };

public:
    struct AuxRegs *get_aux_regs_ptr() 
    {
	return reinterpret_cast<struct AuxRegs *>(PBASE + 0x00215000);	    
    }
};


