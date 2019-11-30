#pragma once

#include "Formula.h"

class Conjunction : public Formula
{
public:

	Formula* child1, * child2;

	Conjunction();
	~Conjunction();

	virtual int getValue(std::map<char, int>* values);

};