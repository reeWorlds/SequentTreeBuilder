#pragma once

#include <string>
#include <vector>
#include "Formula.h"
#include "Variable.h"
#include "Negation.h"
#include "Conjunction.h"
#include "Disjunction.h"
#include "Implication.h"
#include "Sequent.h"
#include "SequentTreeVertex.h"

class Parser
{
	static int isPredicateSymbol(char value);
	static int isSpecialSymbol(char value);
	static int isCorrect0_1_2Formula(std::string);

	static int getFormulaIndex(std::string& formula, int start);
	static std::string	intToString(int number);

	static Formula* parseFormula(std::string formula);

public:
		
	static SequentTreeVertex parseInput(std::string input);

	static int isCorrectFormula(std::string formula);
};