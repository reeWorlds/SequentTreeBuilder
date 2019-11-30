#include "Sequent.h"

int Sequent::isLetter()
{
	if (root->type == FORMULA::variable)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Sequent::toStringRecirsion(Formula* formula, std::string& result)
{
	if (formula->type == FORMULA::variable)
	{
		result += ((Variable*)formula)->name;
	}
	else if (formula->type == FORMULA::negation)
	{
		result.append("!");
		
		if (((Negation*)formula)->child->type != FORMULA::variable)
		{
			result.append("(");
		}

		toStringRecirsion(((Negation*)formula)->child, result);

		if (((Negation*)formula)->child->type != FORMULA::variable)
		{
			result.append(")");
		}
	}
	else if (formula->type == FORMULA::conjunction)
	{
		if (((Conjunction*)formula)->child1->type != FORMULA::variable)
		{
			result.append("(");
		}

		toStringRecirsion(((Conjunction*)formula)->child1, result);

		if (((Conjunction*)formula)->child1->type != FORMULA::variable)
		{
			result.append(")");
		}

		result.append("&");

		if (((Conjunction*)formula)->child2->type != FORMULA::variable)
		{
			result.append("(");
		}

		toStringRecirsion(((Conjunction*)formula)->child2, result);

		if (((Conjunction*)formula)->child2->type != FORMULA::variable)
		{
			result.append(")");
		}
	}
	else if (formula->type == FORMULA::disjunction)
	{
		if (((Disjunction*)formula)->child1->type != FORMULA::variable)
		{
			result.append("(");
		}

		toStringRecirsion(((Disjunction*)formula)->child1, result);

		if (((Disjunction*)formula)->child1->type != FORMULA::variable)
		{
			result.append(")");
		}

		result.append("v");

		if (((Disjunction*)formula)->child2->type != FORMULA::variable)
		{
			result.append("(");
		}

		toStringRecirsion(((Disjunction*)formula)->child2, result);

		if (((Disjunction*)formula)->child2->type != FORMULA::variable)
		{
			result.append(")");
		}
	}
	else if (formula->type == FORMULA::implication)
	{
		if (((Implication*)formula)->child1->type != FORMULA::variable)
		{
			result.append("(");
		}

		toStringRecirsion(((Implication*)formula)->child1, result);

		if (((Implication*)formula)->child1->type != FORMULA::variable)
		{
			result.append(")");
		}

		result.append("->");

		if (((Implication*)formula)->child2->type != FORMULA::variable)
		{
			result.append("(");
		}

		toStringRecirsion(((Implication*)formula)->child2, result);

		if (((Implication*)formula)->child2->type != FORMULA::variable)
		{
			result.append(")");
		}
	}
}

std::string Sequent::toString() // revise
{
	std::string result;

	if (type == SEQUENT::leftSide)
	{
		result = "|-";
	}
	else
	{
		result = "-|";
	}

	toStringRecirsion(root, result);

	return result;
}

void Sequent::copy(Formula*& myNode, Formula*& formula)
{
	if (formula->type == FORMULA::variable)
	{
		myNode = new Variable;
		((Variable*)myNode)->name = ((Variable*)formula)->name;
	}
	else if (formula->type == FORMULA::negation)
	{
		myNode = new Negation;

		copy(((Negation*)myNode)->child, ((Negation*)formula)->child);
	}
	else if (formula->type == FORMULA::conjunction)
	{
		myNode = new Conjunction;

		copy(((Conjunction*)myNode)->child1, ((Conjunction*)formula)->child1);
		copy(((Conjunction*)myNode)->child2, ((Conjunction*)formula)->child2);
	}
	else if (formula->type == FORMULA::disjunction)
	{
		myNode = new Disjunction;

		copy(((Disjunction*)myNode)->child1, ((Disjunction*)formula)->child1);
		copy(((Disjunction*)myNode)->child2, ((Disjunction*)formula)->child2);
	}
	else if (formula->type == FORMULA::implication)
	{
		myNode = new Implication;

		copy(((Implication*)myNode)->child1, ((Implication*)formula)->child1);
		copy(((Implication*)myNode)->child2, ((Implication*)formula)->child2);
	}
}