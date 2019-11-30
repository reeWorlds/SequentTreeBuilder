#include "Negation.h"

Negation::Negation() : child(nullptr)
{
	type = FORMULA::negation;
}

int Negation::getValue(std::map<char, int>* values)
{
	return !(child->getValue(values));
}

Negation::~Negation()
{
	delete child;
}