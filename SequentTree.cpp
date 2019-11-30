#include "SequentTree.h"

SequentTree::SequentTree(std::string input)
{
	tree.push_back(Parser::parseInput(input));

	return;
}

SequentTree::~SequentTree()
{
	for (auto& it : tree)
	{
		for (auto itt : it.sequents)
		{
			delete itt.root;
		}
	}
}

void SequentTree::semiCopyVertex(int oldVertex, int newVertex)
{
	for (auto& it : tree[oldVertex].leftSideLetters)
	{
		tree[newVertex].leftSideLetters.insert(it);
	}
	for (auto& it : tree[oldVertex].rightSideLetters)
	{
		tree[newVertex].rightSideLetters.insert(it);
	}
	for (int j = 0; j<int(tree[oldVertex].sequents.size()) - 1; j++)
	{
		tree[newVertex].sequents.push_back(tree[oldVertex].sequents[j]);
		tree[newVertex].sequents.back().copy((tree[newVertex].sequents.back().root), (tree[oldVertex].sequents[j].root));
	}
}

void SequentTree::buildTree()
{
	for (int i = 0; i<int(tree.size()); i++)
	{
		children.push_back({ -1, -1 });

		if (tree[i].isLeaf())
		{
			continue;
		}

		Sequent lastSequent = tree[i].sequents[int(tree[i].sequents.size()) - 1];

		// P1
		if (lastSequent.root->type == FORMULA::negation && lastSequent.type == SEQUENT::leftSide)
		{
			int position = int(tree.size());
			tree.push_back(SequentTreeVertex());

			children[i].first = position;

			semiCopyVertex(i, position);

			tree[position].sequents.push_back(Sequent());
			tree[position].sequents.back().type = SEQUENT::rightSide;

			//Formula* myNode = tree[position].sequents.back().root;
			//Formula* formula = ((Negation*)(lastSequent.root))->child;
			tree[position].sequents.back().copy(tree[position].sequents.back().root, ((Negation*)(lastSequent.root))->child);

			tree[position].checkLastSequentForVariable();
		}
		// P2
		else if (lastSequent.root->type == FORMULA::negation && lastSequent.type == SEQUENT::rightSide)
		{
			int position = int(tree.size());
			tree.push_back(SequentTreeVertex());

			children[i].first = position;

			semiCopyVertex(i, position);

			tree[position].sequents.push_back(Sequent());
			tree[position].sequents.back().type = SEQUENT::leftSide;
			tree[position].sequents.back().copy(tree[position].sequents.back().root, ((Negation*)lastSequent.root)->child);

			tree[position].checkLastSequentForVariable();
		}
		// P3
		else if (lastSequent.root->type == FORMULA::disjunction && lastSequent.type == SEQUENT::leftSide)
		{
			int position1 = int(tree.size()), position2 = position1 + 1;
			tree.push_back(SequentTreeVertex());
			tree.push_back(SequentTreeVertex());

			children[i].first = position1;
			children[i].second = position2;

			semiCopyVertex(i, position1);
			semiCopyVertex(i, position2);

			tree[position1].sequents.push_back(Sequent());
			tree[position1].sequents.back().type = SEQUENT::leftSide;
			tree[position1].sequents.back().copy(tree[position1].sequents.back().root, ((Disjunction*)lastSequent.root)->child1);

			tree[position1].checkLastSequentForVariable();

			tree[position2].sequents.push_back(Sequent());
			tree[position2].sequents.back().type = SEQUENT::leftSide;
			tree[position2].sequents.back().copy(tree[position2].sequents.back().root, ((Disjunction*)lastSequent.root)->child2);

			tree[position2].checkLastSequentForVariable();
		}
		// P4
		else if (lastSequent.root->type == FORMULA::disjunction && lastSequent.type == SEQUENT::rightSide)
		{
			int position = int(tree.size());
			tree.push_back(SequentTreeVertex());

			children[i].first = position;

			semiCopyVertex(i, position);

			tree[position].sequents.push_back(Sequent());
			tree[position].sequents.back().type = SEQUENT::rightSide;
			tree[position].sequents.back().copy(tree[position].sequents.back().root, ((Disjunction*)lastSequent.root)->child1);
			tree[position].checkLastSequentForVariable();

			tree[position].sequents.push_back(Sequent());
			tree[position].sequents.back().type = SEQUENT::rightSide;
			tree[position].sequents.back().copy(tree[position].sequents.back().root, ((Disjunction*)lastSequent.root)->child2);
			tree[position].checkLastSequentForVariable();
		}
		// P5
		else if (lastSequent.root->type == FORMULA::conjunction && lastSequent.type == SEQUENT::leftSide)
		{
			int position = int(tree.size());
			tree.push_back(SequentTreeVertex());

			children[i].first = position;

			semiCopyVertex(i, position);

			tree[position].sequents.push_back(Sequent());
			tree[position].sequents.back().type = SEQUENT::leftSide;
			tree[position].sequents.back().copy(tree[position].sequents.back().root, ((Conjunction*)lastSequent.root)->child1);
			tree[position].checkLastSequentForVariable();

			tree[position].sequents.push_back(Sequent());
			tree[position].sequents.back().type = SEQUENT::leftSide;
			tree[position].sequents.back().copy(tree[position].sequents.back().root, ((Conjunction*)lastSequent.root)->child2);
			tree[position].checkLastSequentForVariable();
		}
		// P6
		else if (lastSequent.root->type == FORMULA::conjunction && lastSequent.type == SEQUENT::rightSide)
		{
			int position1 = int(tree.size()), position2 = position1 + 1;
			tree.push_back(SequentTreeVertex());
			tree.push_back(SequentTreeVertex());

			children[i].first = position1;
			children[i].second = position2;

			semiCopyVertex(i, position1);
			semiCopyVertex(i, position2);

			tree[position1].sequents.push_back(Sequent());
			tree[position1].sequents.back().type = SEQUENT::rightSide;
			tree[position1].sequents.back().copy(tree[position1].sequents.back().root, ((Conjunction*)lastSequent.root)->child1);

			tree[position1].checkLastSequentForVariable();

			tree[position2].sequents.push_back(Sequent());
			tree[position2].sequents.back().type = SEQUENT::rightSide;
			tree[position2].sequents.back().copy(tree[position2].sequents.back().root, ((Conjunction*)lastSequent.root)->child2);

			tree[position2].checkLastSequentForVariable();
		}
		// P7
		else if (lastSequent.root->type == FORMULA::implication && lastSequent.type == SEQUENT::leftSide)
		{
			int position1 = int(tree.size()), position2 = position1 + 1;
			tree.push_back(SequentTreeVertex());
			tree.push_back(SequentTreeVertex());

			children[i].first = position1;
			children[i].second = position2;

			semiCopyVertex(i, position1);
			semiCopyVertex(i, position2);

			tree[position1].sequents.push_back(Sequent());
			tree[position1].sequents.back().type = SEQUENT::rightSide;
			tree[position1].sequents.back().copy(tree[position1].sequents.back().root, ((Implication*)lastSequent.root)->child1);

			tree[position1].checkLastSequentForVariable();

			tree[position2].sequents.push_back(Sequent());
			tree[position2].sequents.back().type = SEQUENT::leftSide;
			tree[position2].sequents.back().copy(tree[position2].sequents.back().root, ((Implication*)lastSequent.root)->child2);

			tree[position2].checkLastSequentForVariable();
		}
		// P8
		else if (lastSequent.root->type == FORMULA::implication && lastSequent.type == SEQUENT::rightSide)
		{
			int position = int(tree.size());
			tree.push_back(SequentTreeVertex());

			children[i].first = position;

			semiCopyVertex(i, position);

			tree[position].sequents.push_back(Sequent());
			tree[position].sequents.back().type = SEQUENT::leftSide;
			tree[position].sequents.back().copy(tree[position].sequents.back().root, ((Implication*)lastSequent.root)->child1);
			tree[position].checkLastSequentForVariable();

			tree[position].sequents.push_back(Sequent());
			tree[position].sequents.back().type = SEQUENT::rightSide;
			tree[position].sequents.back().copy(tree[position].sequents.back().root, ((Implication*)lastSequent.root)->child2);
			tree[position].checkLastSequentForVariable();
		}
	}
}

void SequentTree::buildQTreeWidget(QTreeWidget* treeWidget)
{
	colors.resize(tree.size());

	QTreeWidgetItem* root = new QTreeWidgetItem(treeWidget);
	QString text = QString::fromStdString(tree[0].toString());
	root->setText(0, text);
	treeWidget->addTopLevelItem(root);
	
	if (children[0].first != -1)
	{
		buildQTreeWidgetRecursion(root, children[0].first);
	}

	if (children[0].second != -1)
	{
		buildQTreeWidgetRecursion(root, children[0].second);
	}

	processColor(0);

	if (colors[0] == MYCOLOR::green)
	{
		root->setBackground(0, Qt::green);
	}
	else
	{
		root->setBackground(0, Qt::red);
	}
}

void SequentTree::buildQTreeWidgetRecursion(QTreeWidgetItem* parent, int position)
{
	QTreeWidgetItem* item = new QTreeWidgetItem(parent);
	QString text = QString::fromStdString(tree[position].toString());
	item->setText(0, text);
	parent->addChild(item);

	if (children[position].first != -1)
	{
		buildQTreeWidgetRecursion(item, children[position].first);
	}

	if (children[position].second != -1)
	{
		buildQTreeWidgetRecursion(item, children[position].second);
	}

	processColor(position);

	if (colors[position] == MYCOLOR::green)
	{
		item->setBackground(0, Qt::green);
	}
	else
	{
		item->setBackground(0, Qt::red);
	}
}

void SequentTree::processColor(int position)
{
	if (children[position].first == -1)
	{
		if (tree[position].isGoodLeaf())
		{
			colors[position] = MYCOLOR::green;
		}
	}
	else if (children[position].second == -1)
	{
		colors[position] = colors[children[position].first];
	}
	else
	{
		if (colors[children[position].first] == MYCOLOR::red || colors[children[position].second] == MYCOLOR::red)
		{
			colors[position] = MYCOLOR::red;
		}
		else
		{
			colors[position] = MYCOLOR::green;
		}
	}
}