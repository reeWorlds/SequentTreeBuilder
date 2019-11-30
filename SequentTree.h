#pragma once

#include <QtWidgets>
#include <QTreeWidget>

#include "Formula.h"
#include "Variable.h"
#include "Negation.h"
#include "Conjunction.h"
#include "Disjunction.h"
#include "Implication.h"
#include "Sequent.h"
#include "SequentTreeVertex.h"
#include "Parser.h"

#include <string>
#include <vector>
#include <algorithm>

enum MYCOLOR
{
	red,
	green
};

class SequentTree
{
	std::vector<int> colors;

	void semiCopyVertex(int oldVertex, int newVertex);

	void buildQTreeWidgetRecursion(QTreeWidgetItem* parent, int position);

	void processColor(int position);

public:
	std::vector<std::pair<int, int> > children;

	std::vector<SequentTreeVertex> tree;

	SequentTree(std::string inout);
	~SequentTree();

	void buildTree();

	void buildQTreeWidget(QTreeWidget* treeWidget);
};