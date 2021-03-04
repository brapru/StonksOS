#pragma once

#include "types.hpp"
#include "stonksos/stdio.hpp"

template <typename Regmap>
class Peripheral {
public:
	Peripheral(PhysicalAddress address)
		: m_address( address )
	{
	}

	PhysicalAddress get_address() { return m_address; } 
	Regmap* get_regmap() { return reinterpret_cast<Regmap *>(m_address); }

	/*TODO
	u64 read_register();
	void write_register();
	*/

private:
	PhysicalAddress m_address;
	Regmap m_regmap;
};
