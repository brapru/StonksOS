#include "peripherals/gpio.hpp"
#include "utils.hpp"
#include "types.hpp"

void gpio_pin_set_func(u8 pin, GpioFunc f) 
{
	u8 bitstart = (pin * 3) % 30;
	u8 reg = pin / 10;

	u32 selector = REGS_GPIO->func_select[reg];
	selector &= ~(7 << bitstart);
	selector |= (f << bitstart);

	REGS_GPIO->func_select[reg] = selector;
}

void gpio_pin_enable(u8 pin)
{
	REGS_GPIO->pupd_enable = 0;
	kernel::delay(150);
	REGS_GPIO->pupd_enable_clocks[pin / 32] = 1 << (pin % 32);
	kernel::delay(150);
	REGS_GPIO->pupd_enable = 0;
	REGS_GPIO->pupd_enable_clocks[pin / 32] = 0;
}
