#pragma once

#include "Formula.h"

class Variable : public Formula
{
public:

	char name;

	Variable();

	virtual int getValue(std::map<char, int>* value);
};