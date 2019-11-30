#include "Disjunction.h"

Disjunction::Disjunction() : child1(nullptr), child2(nullptr)
{
	type = FORMULA::disjunction;
}

int Disjunction::getValue(std::map<char, int>* values)
{
	return ((child1->getValue(values)) | (child2->getValue(values)));
}

Disjunction::~Disjunction()
{
	delete child1;
	delete child2;
}