#pragma once

#include "Formula.h"

class Negation : public Formula
{
public:

	Formula* child;

	Negation();
	~Negation();

	virtual int getValue(std::map<char, int>* value);
};