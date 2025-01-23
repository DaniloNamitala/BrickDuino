#include "ModalNewVariable.h"
#include <QtCore>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>

ModalNewVariable::ModalNewVariable(QWidget* parent) : QDialog(parent) {
	setModal(true);
	rejected = false;
	setWindowTitle("Nome da Variavel");
	lineEditVar = new LineEdit(this);
	QPushButton* buttonCreate = new QPushButton("Criar");
	buttonCreate->setCursor(Qt::PointingHandCursor);
	comboTypes = new QComboBox();
	comboTypes->addItem("STRING");
	comboTypes->addItem("INT");
	comboTypes->addItem("FLOAT");
	comboTypes->addItem("BOOL");

	//Label* label = new QLabel("Nome da Variavel:");

	QGridLayout* layout = new QGridLayout();
	//layout->addWidget(label);
	layout->addWidget(comboTypes, 0, 0);
	layout->addWidget(lineEditVar, 0, 1);
	layout->addWidget(buttonCreate, 1, 0, 1, 2);

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

void ModalNewVariable::closeEvent(QCloseEvent* event)
{
	event->ignore();
	rejected = true;
	this->reject();
}

void ModalNewVariable::lineEditDone() {
	QString text = this->lineEditVar->text().trimmed();
	if (text.isEmpty() || text.contains(" ")) {
		int r = QMessageBox::warning(this, tr("Erro"), tr("O nome da variavel nao pode ser vazio ou conter espacos!!"));
		return;
	}
	
	if (!rejected) // gambiarra para nao executar o done quando perde o foco no input
		this->accept();


}

QString ModalNewVariable::getType() {
	return this->comboTypes->currentText().trimmed();
}

QString ModalNewVariable::getText() {
	return this->lineEditVar->text().trimmed();
}