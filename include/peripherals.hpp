#pragma once

template <class R>
class Peripheral {
public:
	Peripheral(PhysicalAddress address)
		: m_address{ address }
	{
	}

	PhysicalAddress get() const { return m_address; } 
	R* get_as_ptr() { return reinterpret_cast<R *>(m_address); }

private:
	PhysicalAddress m_address;
	R m_regmap;
};
