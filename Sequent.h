#pragma once

#include <string>

#include "Formula.h"
#include "Variable.h"
#include "Negation.h"
#include "Conjunction.h"
#include "Disjunction.h"
#include "Implication.h"

enum SEQUENT
{
	rightSide,
	leftSide
};

class Sequent
{
	void toStringRecirsion(Formula* formula, std::string& relust);

public:

	int type;

	Formula* root;

	int isLetter();
	
	std::string toString();

	void copy(Formula*& myNode, Formula*& formula);
};