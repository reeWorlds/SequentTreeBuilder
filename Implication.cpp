#include "Implication.h"

Implication::Implication() : child1(nullptr), child2(nullptr)
{
	type = FORMULA::implication;
}

int Implication::getValue(std::map<char, int>* values)
{
	return ((!(child1->getValue(values))) | (child2->getValue(values)));
}

Implication::~Implication()
{
	delete child1;
	delete child2;
}