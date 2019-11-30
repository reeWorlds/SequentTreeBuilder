#include "Parser.h"

int Parser::isPredicateSymbol(char value)
{
	if ('A' <= value && value <='Z')
	{
		return 1;
	}

	return 0;
}

int Parser::isSpecialSymbol(char value)
{
	if (value == '|' || value == '=' || value == '(' || value == ')' || value == ',' ||
		value == '!' || value == 'v' || value == '&' || value == '-' || value == '>')
	{
		return 1;
	}

	return 0;
}

int Parser::isCorrect0_1_2Formula(std::string formula) // 0, 1, (, ), 2
{
	if (formula.empty())
	{
		return 0;
	}

	if (int(formula.size()) == 1)
	{
		if (formula[0] == '1')
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	int i, parenthesesCount = 0;

	for (i = 0; i + 1 < int(formula.size()); i++)
	{
		if (formula[i] == '0')
		{
			if (formula[i+1] == '0' || formula[i+1] == ')')
			{
				return 0;
			}
		}
		if (formula[i] == '1')
		{
			if (formula[i + 1] == '1' || formula[i + 1] == '(' || formula[i+1] == '2')
			{
				return 0;
			}
		}
		if (formula[i] == '2')
		{
			if (formula[i + 1] == '0' || formula[i + 1] == ')')
			{
				return 0;
			}
		}
		if (formula[i] == '(')
		{
			if (formula[i + 1] == '0' || formula[i + 1] == ')')
			{
				return 0;
			}
		}
		if (formula[i] == ')')
		{
			if (formula[i + 1] == '1' || formula[i + 1] == '(' || formula[i + 1] == '2')
			{
				return 0;
			}
		}
	}

	if (formula[0] != '1'  && formula[0] != '(' && formula[i] == '2')
	{
		return 0;
	}

	if (formula.back() != '1' && formula.back() != ')')
	{
		return 0;
	}

	for (i = 0; i<int(formula.size()); i++)
	{
		if (formula[i] == '(')
		{
			parenthesesCount++;
		}
		if (parenthesesCount == ')')
		{
			parenthesesCount--;

			if (parenthesesCount < 0)
			{
				return 0;
			}
		}
	}
	if (parenthesesCount != 0)
	{
		return 0;
	}

	return 1;
}

int Parser::isCorrectFormula(std::string formula)
{
	int i;

	// delete space and tab
	{
		std::string tempFormula;

		for (i = 0; i<int(formula.size()); i++)
		{
			if (formula[i] != ' ' && formula[i] != '\t')
			{
				tempFormula += formula[i];
			}
		}

		formula = tempFormula;
	}

	if (formula.empty())
	{
		return 0;
	}

	// check that all symbols are correct
	for (i = 0; i<int(formula.size()); i++)
	{
		if ((!isPredicateSymbol(formula[i])) && (!isSpecialSymbol(formula[i])))
		{
			return 0;
		}
	}

	// make 0-1 string
	int countI = 0, countEqual = 0;

	for (i = 0; i<int(formula.size()); i++)
	{
		if (formula[i] == '|')
		{
			countI++;
		}
		if (formula[i] == '=')
		{
			countEqual++;
		}
	}

	if (countEqual != 1 || countI != 1)
	{
		return 0;
	}

	{
		std::string tempFormula;

		for (i = 0; i<int(formula.size()); i++)
		{
			if (formula[i] != '|' && formula[i] != '=')
			{
				tempFormula += formula[i];

				continue;
			}

			if (formula[i] == '|')
			{
				if ((i + 1 == int(formula.size())) || formula[i + 1] != '=')
				{
					return 0;
				}

				if (i + 2 != int(formula.size()))
				{
					tempFormula += ',';
				}
			}
		}

		formula = tempFormula;
	}

	std::string tempFormula;
	std::vector<std::string> formulas;
	for (i = 0; i < int(formula.size()); i++)
	{
		if (formula[i] == ',')
		{
			formulas.push_back(tempFormula);
			tempFormula.clear();

			continue;
		}

		if (formula[i] == '(' || formula[i] == ')')
		{
			tempFormula += formula[i];
		}
		else if (isPredicateSymbol(formula[i]))
		{
			tempFormula += '1';
		}
		else if(formula[i] == '!')
		{
			tempFormula += '2';
		}
		else if (formula[i] == '&' || formula[i] == 'v')
		{
			tempFormula += '0';
		}
		else if (formula[i] == '-')
		{
			if (i + 1 == int(formula.size()))
			{
				return 0;
			}

			if (formula[i + 1] != '>')
			{
				return 0;
			}

			tempFormula += '0';
			i++;
		}
		else
		{
			return 0;
		}
	}
	formulas.push_back(tempFormula);

	for (i = 0; i < int(formulas.size()); i++)
	{
		if (!isCorrect0_1_2Formula(formulas[i]))
		{
			return 0;
		}
	}

	return 1;
}

int Parser::getFormulaIndex(std::string& formula, int start)
{
	int result = 0;

	if (formula[start] == '{')
	{
		start++;
	}

	while (formula[start] != '}')
	{
		result *= 10;
		result += (formula[start] - '0');
		start++;
	}

	return result;
}

std::string	Parser::intToString(int number)
{
	if (number == 0)
	{
		return "0";
	}

	std::string result;
	while (number > 0)
	{
		result += char(number % 10 + '0');
		number /= 10;
	}

	reverse(result.begin(), result.end());

	return result;
}

Formula* Parser::parseFormula(std::string formula)
{
	std::vector<Formula*> formulas;

	// process parenthesis
	for (int i = 0; i < int(formula.size()); i++)
	{
		if (formula[i] == '(')
		{
			std::string insideFormula;
			int start_ = i, end_ = i + 1, count = 1;
			for (end_ = i + 1;; end_++)
			{
				if (formula[end_] == '(')
				{
					count++;
				}
				if (formula[end_] == ')')
				{
					count--;
				}
				if (count == 0)
				{
					break;
				}
				insideFormula += formula[end_];
			}

			int formulaIndex = formulas.size();

			formulas.push_back(parseFormula(insideFormula));

			std::string newFormula;
			for (int j = 0; j < start_; j++)
			{
				newFormula += formula[j];
			}
			newFormula += "{";
			newFormula += intToString(formulaIndex);
			newFormula += "}";
			i = newFormula.size();
			i--;
			for (int j = end_ + 1; j < int(formula.size()); j++)
			{
				newFormula += formula[j];
			}

			formula = newFormula;
		}
	}

	// process variables
	for (int i = 0; i < int(formula.size()); i++)
	{
		if ('A' <= formula[i] && formula[i] <= 'Z')
		{
			int formulaIndex = formulas.size(), pos = i;

			formulas.push_back(new Variable());
			((Variable*)formulas.back())->name = formula[i];

			std::string newFormula;
			for (int j = 0; j < pos; j++)
			{
				newFormula += formula[j];
			}
			newFormula += "{";
			newFormula += intToString(formulaIndex);
			newFormula += "}";
			i = newFormula.size();
			i--;
			for (int j = pos + 1; j < int(formula.size()); j++)
			{
				newFormula += formula[j];
			}

			formula = newFormula;
		}
	}

	// process negation
	for (int i = int(formula.size() - 1); i >= 0; i--)
	{
		if (formula[i] == '!')
		{
			int start_ = i + 1, end_ = i + 2;
			while (formula[end_] != '}')
			{
				end_++;
			}

			int childFormulaIndex = getFormulaIndex(formula, start_);
			int formulaIndex = formulas.size();

			formulas.push_back(new Negation);
			((Negation*)formulas.back())->child = formulas[childFormulaIndex];

			std::string newFormula;
			for (int j = 0; j < i; j++)
			{
				newFormula += formula[j];
			}
			newFormula += "{";
			newFormula += intToString(formulaIndex);
			newFormula += "}";
			for (int j = end_ + 1; j < int(formula.size()); j++)
			{
				newFormula += formula[j];
			}

			formula = newFormula;
		}
	}

	//process conjunction
	for (int i = 0; i < int(formula.size()); i++)
	{
		if (formula[i] == '&')
		{
			int start1 = i - 2, end1 = i - 1;
			while (formula[start1] != '{')
			{
				start1--;
			}

			int start2 = i + 1, end2 = i + 2;
			while (formula[end2] != '}')
			{
				end2++;
			}

			int child1FormulaIndex = getFormulaIndex(formula, start1);
			int child2FormulaIndex = getFormulaIndex(formula, start2);
			int formulaIndex = formulas.size();

			formulas.push_back(new Conjunction);
			((Conjunction*)formulas.back())->child1 = formulas[child1FormulaIndex];
			((Conjunction*)formulas.back())->child2 = formulas[child2FormulaIndex];

			std::string newFormula;
			for (int j = 0; j < start1; j++)
			{
				newFormula += formula[j];
			}
			newFormula += "{";
			newFormula += intToString(formulaIndex);
			newFormula += "}";
			i = newFormula.size();
			i--;
			for (int j = end2 + 1; j < int(formula.size()); j++)
			{
				newFormula += formula[j];
			}

			formula = newFormula;
		}
	}

	//process disjunction
	for (int i = 0; i < int(formula.size()); i++)
	{
		if (formula[i] == 'v')
		{
			int start1 = i - 2, end1 = i - 1;
			while (formula[start1] != '{')
			{
				start1--;
			}

			int start2 = i + 1, end2 = i + 2;
			while (formula[end2] != '}')
			{
				end2++;
			}

			int child1FormulaIndex = getFormulaIndex(formula, start1);
			int child2FormulaIndex = getFormulaIndex(formula, start2);
			int formulaIndex = formulas.size();

			formulas.push_back(new Disjunction);
			((Disjunction*)formulas.back())->child1 = formulas[child1FormulaIndex];
			((Disjunction*)formulas.back())->child2 = formulas[child2FormulaIndex];

			std::string newFormula;
			for (int j = 0; j < start1; j++)
			{
				newFormula += formula[j];
			}
			newFormula += "{";
			newFormula += intToString(formulaIndex);
			newFormula += "}";
			i = newFormula.size();
			i--;
			for (int j = end2 + 1; j < int(formula.size()); j++)
			{
				newFormula += formula[j];
			}

			formula = newFormula;
		}
	}

	//process implication
	for (int i = int(formula.size()) - 1; i >= 1; i--)
	{
		if (formula[i] == '-' && formula[i + 1] == '>' && formula[i - 1] != '<')
		{
			int start1 = i - 2, end1 = i - 1;
			while (formula[start1] != '{')
			{
				start1--;
			}

			int start2 = i + 2, end2 = i + 3;
			while (formula[end2] != '}')
			{
				end2++;
			}

			int child1FormulaIndex = getFormulaIndex(formula, start1);
			int child2FormulaIndex = getFormulaIndex(formula, start2);
			int formulaIndex = formulas.size();

			formulas.push_back(new Implication);
			((Implication*)formulas.back())->child1 = formulas[child1FormulaIndex];
			((Implication*)formulas.back())->child2 = formulas[child2FormulaIndex];

			std::string newFormula;
			for (int j = 0; j < start1; j++)
			{
				newFormula += formula[j];
			}
			newFormula += "{";
			newFormula += intToString(formulaIndex);
			newFormula += "}";
			i = newFormula.size();
			i--;
			for (int j = end2 + 1; j < int(formula.size()); j++)
			{
				newFormula += formula[j];
			}

			formula = newFormula;
		}
	}

	return formulas[getFormulaIndex(formula, 0)];
}

SequentTreeVertex Parser::parseInput(std::string input)
{
	int isRightSide = 0;

	SequentTreeVertex result;

	for (int i = 0; i < int(input.size()); i++)
	{
		if (input[i] == '=')
		{
			isRightSide = 1;

			continue;
		}

		if (input[i] == '|')
		{
			isRightSide = 1;
			i++;

			continue;
		}

		if (input[i] == ',')
		{
			continue;
		}

		std::string formula;
		int statr_ = i, end_ = i;

		while (end_ < int(input.size()) && input[end_] != ',' && input[end_] != '|')
		{
			formula += input[end_];
			end_++;
		}
		i = end_ - 1;

		Sequent sequent;

		sequent.root = parseFormula(formula);

		if (isRightSide == 1)
		{
			sequent.type = SEQUENT::rightSide;
		}
		else
		{
			sequent.type = SEQUENT::leftSide;
		}

		if (sequent.root->type == FORMULA::variable)
		{
			if (sequent.type == SEQUENT::leftSide)
			{
				result.leftSideLetters.insert(((Variable*)sequent.root)->name);
			}
			else
			{
				result.rightSideLetters.insert(((Variable*)sequent.root)->name);
			}

			delete sequent.root;
		}
		else
		{
			result.sequents.push_back(sequent);
		}
	}

	return result;
}
