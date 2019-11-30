#pragma once

#include <map>

enum FORMULA
{
	variable,
	negation,
	conjunction,
	disjunction,
	implication
};

class Formula
{
public:

	FORMULA type;

	virtual int getValue(std::map<char, int>* values) = 0;

};