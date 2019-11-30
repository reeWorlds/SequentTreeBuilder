#pragma once

#include "Formula.h"

class Disjunction : public Formula
{
public:

	Formula* child1, * child2;

	Disjunction();
	~Disjunction();

	virtual int getValue(std::map<char, int>* values);
};