#pragma once

#include "Formula.h"

class Implication : public Formula
{
public:

	Formula* child1, * child2;

	Implication();
	~Implication();

	virtual int getValue(std::map<char, int>* values);

};