#include "Conjunction.h"

Conjunction::Conjunction() : child1(nullptr), child2(nullptr)
{
	type = FORMULA::conjunction;
}

int Conjunction::getValue(std::map<char, int>* values)
{
	return ((child1->getValue(values)) & (child2->getValue(values)));
}

Conjunction::~Conjunction()
{
	delete child1;
	delete child2;
}
