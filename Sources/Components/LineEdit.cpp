#include "LineEdit.h"


LineEdit::LineEdit(QWidget* parent) : QLineEdit(parent) {

}

void LineEdit::focusInEvent(QFocusEvent* event) {
	initialText = text();
}

void LineEdit::keyReleaseEvent(QKeyEvent* event) {
	int key = event->key();
	if (key == Qt::Key_Escape) {
		setText(initialText);
		emit inputRejected();
	}
	else if (key == Qt::Key_Return) {
		emit editingFinished();
	}
	QLineEdit::keyReleaseEvent(event);
}
