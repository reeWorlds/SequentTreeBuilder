#pragma once

#include "Formula.h"
#include "Variable.h"
#include "Negation.h"
#include "Conjunction.h"
#include "Disjunction.h"
#include "Implication.h"
#include "Sequent.h"

#include <vector>
#include <set>

class SequentTreeVertex
{
public:

	std::set<char> leftSideLetters; // of |=
	std::set<char> rightSideLetters; // of |=

	std::vector<Sequent> sequents;

	int isLeaf();
	int isGoodLeaf();

	void checkLastSequentForVariable();

	std::string toString();
};

