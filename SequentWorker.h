#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QTreeView>
#include "ui_SequentWorker.h"
#include <string>

#include "SequentTree.h"
#include "Parser.h"

class SequentWorker : public QMainWindow
{
	Q_OBJECT

public:
	SequentWorker(QWidget *parent = Q_NULLPTR);

private:

	Ui::SequentWorkerClass ui;

public slots:
	void processSequents();
};

/*
1) A->B,C->D,AvC|=BvD
2) AvB,B->C,!Av!C|=!AvD
3) B->A,C->D,B&!D|=A&!C
4) A->C,B->D,AvB|=D&C
5) A->B,C->D,!BvD&C|=!Av!C
6) !A->B,Q->D,!Bv!D|=Av!Q
7) A->C,!D->B,!A->!B|=!C->D
8) AvBvC,!AvC,!B|=!C
9) AvB->C->D,!A&!B|=C&!D
10)A->B,C->D,!Bv!D|=!Av!C
11)A->B,C->D|=AvC->BvD
12)A->B,C->D|=A&C->B&D
13)A->B,C->D|=AvC->B&D
14)A->B,C->D|=A&C->B&D
*/