#pragma once
#include "stonksos/stdio.hpp"

class Stdlib 
{
private:
	Stdio stdio;	

public:
	Stdio *get_stdio_object(void) { return &stdio; }

	__attribute__((__noreturn__))
	void abort(void);
};
