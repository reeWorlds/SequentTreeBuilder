#include "SequentWorker.h"

SequentWorker::SequentWorker(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QString es = "";
	
	ui.treeWidget->setStyleSheet("QTreeView::branch:has-siblings:!adjoins-item {border-image: url(vline.png) 0;} " + es +
		"QTreeView::branch:has-siblings:adjoins-item {border-image: url(branch-more.png) 0;} " + es +
		"QTreeView::branch:!has-children:!has-siblings:adjoins-item {border-image: url(branch-end.png) 0;} " + es +
		"QTreeView::branch:has-children:!has-siblings:closed,QTreeView::branch:closed:has-children:has-siblings" + es +
		"{border-image: none; image: url(branch-closed.png);} " + es +
		"QTreeView::branch:open:has-children:!has-siblings,QTreeView::branch:open:has-children:has-siblings" + es +
		"{border-image: none; image: url(branch-open.png);}");
	
	
	ui.treeWidget->setHeaderLabel("tree");

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(processSequents()));
}

void SequentWorker::processSequents()
{
	std::string input = ui.lineEdit->text().toStdString();

	if (input == "")
	{
		return;
	}

	if (!(Parser::isCorrectFormula(input)))
	{
		QMessageBox::warning(this, "Error!", "Incorrect input!");

		return;
	}

	ui.treeWidget->clear();	

	SequentTree tree(input);
	tree.buildTree();
	tree.buildQTreeWidget(ui.treeWidget);
	ui.treeWidget->expandAll();
}