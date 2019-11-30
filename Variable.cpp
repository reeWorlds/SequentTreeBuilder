#include "Variable.h"

Variable::Variable() : name(-1)
{
	type = FORMULA::variable;
}

int Variable::getValue(std::map<char, int>* values)
{
	return values->operator[](name);
}