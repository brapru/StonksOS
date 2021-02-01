#pragma once

extern "C" void delay(unsigned long ticks);
extern "C" void put32(unsigned long address, unsigned int value);
extern "C" unsigned int get32(unsigned long address);
