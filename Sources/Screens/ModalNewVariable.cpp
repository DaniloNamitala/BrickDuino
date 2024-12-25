#include "ModalNewVariable.h"
#include <QtCore>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

ModalNewVariable::ModalNewVariable(QWidget* parent) : QDialog(parent) {
	setModal(true);
	rejected = false;
	setWindowTitle("Nome da Variavel");
	lineEditVar = new LineEdit(this);
	QPushButton* buttonCreate = new QPushButton("Criar");
	buttonCreate->setCursor(Qt::PointingHandCursor);
	// QLabel* label = new QLabel("Nome da Variavel:");

	QVBoxLayout* layout = new QVBoxLayout();
	//layout->addWidget(label);
	layout->addWidget(lineEditVar);
	layout->addWidget(buttonCreate);

	connect(lineEditVar, &QLineEdit::editingFinished, this, &ModalNewVariable::lineEditDone);
	connect(buttonCreate, &QPushButton::clicked, this, &ModalNewVariable::lineEditDone);

	setLayout(layout);
}


void ModalNewVariable::keyPressEvent(QKeyEvent* event) {
	int key = event->key();
	if (key == Qt::Key_Escape) {
		rejected = true;
		this->reject();
	}
}


void ModalNewVariable::lineEditDone() {
	if (!rejected) // gambiarra para sar recusando com esc
		this->accept();
}

QString ModalNewVariable::getText() {
	return this->lineEditVar->text();
}