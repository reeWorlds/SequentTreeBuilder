#include "SequentTreeVertex.h"

int SequentTreeVertex::isLeaf()
{
	return sequents.empty();
}

int SequentTreeVertex::isGoodLeaf()
{
	if (!isLeaf())
	{
		return 0;
	}

	for (auto it : leftSideLetters)
	{
		if (rightSideLetters.find(it) != rightSideLetters.end())
		{
			return 1;
		}
	}

	return 0;
}

std::string SequentTreeVertex::toString()
{
	std::string formula;
	std::vector<std::string> info;

	for (auto& it : leftSideLetters)
	{
		std::string val = "|-";
		val += char(it);

		info.push_back(val);
	}
	for (auto& it : rightSideLetters)
	{
		std::string val = "-|";
		val += char(it);

		info.push_back(val);
	}

	for (auto& it : sequents)
	{
		info.push_back(it.toString());
	}

	for (int i = 0; i<int(info.size()); i++)
	{
		formula += info[i];
		if (i + 1 != int(info.size()))
		{
			formula += ", ";
		}
	}

	return formula;
}

void SequentTreeVertex::checkLastSequentForVariable()
{
	if (sequents.back().root->type == FORMULA::variable)
	{
		if (sequents.back().type == SEQUENT::leftSide)
		{
			leftSideLetters.insert(((Variable*)sequents.back().root)->name);
		}
		else
		{
			rightSideLetters.insert(((Variable*)sequents.back().root)->name);
		}

		delete sequents.back().root;

		sequents.pop_back();
	}
}