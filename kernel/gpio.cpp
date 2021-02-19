#include "peripherals/gpio.hpp"
#include "utils.hpp"
#include "types.hpp"

Gpio g_gpio;

void Gpio::gpio_pin_set_func(u8 pin, GpioFunc f) 
{
	u8 bitstart = (pin * 3) % 30;
	u8 reg = pin / 10;

	u32 selector = get_gpio_regs_ptr()->func_select[reg];
	selector &= ~(7 << bitstart);
	selector |= (f << bitstart);

	get_gpio_regs_ptr()->func_select[reg] = selector;
}

void Gpio::gpio_pin_enable(u8 pin)
{
	get_gpio_regs_ptr()->pupd_enable = 0;
	kernel::delay(150);
	get_gpio_regs_ptr()->pupd_enable_clocks[pin / 32] = 1 << (pin % 32);
	kernel::delay(150);
	get_gpio_regs_ptr()->pupd_enable = 0;
	get_gpio_regs_ptr()->pupd_enable_clocks[pin / 32] = 0;
}
