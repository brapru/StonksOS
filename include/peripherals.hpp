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
	Regmap* get_as_ptr() { return reinterpret_cast<Regmap *>(m_address); }

	void write_register(u64 offset, u32 value) { m_regmap.get_as_ptr()->offset = value; };
	void write_register(u32 offset, u32 value) { m_regmap.get_as_ptr()->offset = value; };
	void write_register(u64 offset, u64 value) { m_regmap.get_as_ptr()->offset = value; };
	void read_register(u32 offset){ m_regmap.get_as_ptr()->offset; };
	void read_register(u64 offset){ m_regmap.get_as_ptr()->offset; };

private:
	PhysicalAddress m_address;
	Regmap m_regmap;
};
