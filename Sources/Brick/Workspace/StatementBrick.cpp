#include "StatementBrick.h"

#include <QPainter>
#include <QPainterPath>
#include <QCursor>
#include "Shadow.h"
#include "Util.h"
#include "StatementBrickPainter.h"
#include "ConfigBrickIf.h"
#include "ValueBrick.h"
#include "string.h"

Workspace::StatementBrick::StatementBrick(QWidget* parent, const char* message, const char* name, QColor color) : Workspace::Brick(parent, message, name, color) {
	painter = new StatementBrickPainter();
	_showConfig = strcmp(name, "if_statement") == 0 || strcmp(name, "case_statement") == 0 || strcmp(name, "for_statement") == 0;
	for (int i = 0; i < QString(message).count("%s"); i++) {
		this->statements.append(Statement());
	}
	shadow_statement_idx = -1;
	lines.clear();
	lines = QString(message).split("%s");
	lines.removeAll("");

	recalculateSize();
}

Workspace::StatementBrick::StatementBrick(const char* message, const char* name, QColor color) : Workspace::StatementBrick(nullptr, message, name, color) { }

void Workspace::StatementBrick::removeBrick(Workspace::Brick* brick) {
	for (int i = 0; i < statements.count(); i++) {
		if (statements[i].head() == brick) {
			statements[i].remove(brick);
			break;
		}
	}
	recalculateSize();
}

void Workspace::StatementBrick::addCase() {
	//"CASO %1 %s PADRAO %s"
	int param = params.count() + 1;
	QString line = QString("CASO %%1").arg(param);
	int idx_ins = message.indexOf("PADRAO");
	message.insert(idx_ins, line + " %s ");
	int idx = lines.count() - 1;

	lines.insert(idx, line);
	params.append(Parameter(ValueType::BOOL, "case_value"));
	statements.insert(idx, Statement());

	recalculateSize();
}

void Workspace::StatementBrick::removeCase() {
	QRegularExpression re("CASO %[0-9]+");
	int idx = lines.lastIndexOf(re);
	if (idx >= statements.count() || idx < 0) return;
	if (statements[idx].head() != nullptr) return;

	QString line = lines.at(idx);
	QString s = message.remove(line + " %s ");
	if (s.isEmpty())
		message.remove(line + " %s");

	lines.removeAt(idx);
	params.removeLast();
	statements.removeAt(idx);

	recalculateSize();
}

void Workspace::StatementBrick::addCondition() {
	int param = params.count() + 1;
	QString line = QString("SENAO SE %%1").arg(param);
	if (message.contains("SENAO %s")) {
		int idx_ins = message.indexOf("SENAO %s");
		message.insert(idx_ins, line + " %s ");
	}
	else {
		message += " " + line + " %s";
	}
	int idx = lines.count();
	if (lines.last().trimmed() == "SENAO")
		idx--;

	lines.insert(idx, line);
	params.append(Parameter(ValueType::BOOL, "condition"));
	statements.insert(idx, Statement());

	recalculateSize();
}

void Workspace::StatementBrick::addElse() {
	if (lines.last().trimmed() == "SENAO") return;
	int param = params.count() + 1;
	QString line = QString("SENAO").arg(param);
	message += " " + line + " %s";
	lines.append(line);
	statements.append(Statement());

	recalculateSize();
}

void Workspace::StatementBrick::removeCondition() {
	QRegularExpression re("SENAO SE %[0-9]+");
	int idx = lines.lastIndexOf(re);
	if (idx >= statements.count() || idx < 0) return;
	if (statements[idx].head() != nullptr) return;

	QString line = lines.at(idx);
	QString s = message.remove(line + " %s ");
	if (s.contains(line))
		message.remove(" " + line + " %s");

	lines.removeAt(idx);
	params.removeLast();
	statements.removeAt(idx);

	recalculateSize();
}

BrickType Workspace::StatementBrick::getType() {
	return BrickType::STATEMENT;
}

void Workspace::StatementBrick::removeElse() {
	if (lines.last().trimmed() != "SENAO") return;
	if (statements.last().head() != nullptr) return;

	QString line = lines.last();
	if (!line.startsWith(" ")) line = " " + line;
	if (!line.endsWith(" ")) line += " ";
	message.remove(line + "%s");

	lines.removeLast();
	statements.removeLast();

	recalculateSize();
}

void Workspace::StatementBrick::openConfig() {
	if (!showConfig()) return;

	if (this->name == "for_statement") {
		Workspace::Brick* _brick = new Workspace::ValueBrick(this->variable.toStdString().c_str(), "variable_call", QColor("#82101b"));
		_brick->setParent(this->parentWidget());
		_brick->setZOrder(0);
		_brick->move(mousePos + this->pos() + QPoint(30, 0));
		return;
	}

	ConfigBrickIf* config = new ConfigBrickIf(this, name);
	config->show();
}

void Workspace::StatementBrick::insertBrick(Brick* brick, int st_idx) {
	statements[st_idx].insert(brick);
	this->stackUnder(brick);
	int y = pos().y() + PIN_H;
	for (int i = 0; i < st_idx; i++) {
		y += headerSize(i).height() + statements[i].height();
	}

	QPoint p(pos().x() + BRACKET_WIDTH, y + headerSize(st_idx).height());

	brick->setOwner(this);
	brick->setZOrder(z_order + 1);
	brick->move(p);
	recalculateSize();
}

void Workspace::StatementBrick::recalculateSize() {
	Workspace::Brick::recalculateSize();

	int y = this->pos().y() + PIN_H;
	for (int i = 0; i < statements.count(); i++) {
		QPoint p(this->pos().x() + BRACKET_WIDTH, y + headerSize(i).height());
		if (statements[i].head() != nullptr)
			statements[i].head()->move(p);
		y += headerSize(i).height() + statements[i].height();
	}
}

void Workspace::StatementBrick::move(const QPoint& pos) {
	Workspace::Brick::move(pos);

	int y = pos.y();
	for (int i = 0; i < statements.count(); i++) {
		QPoint p(pos.x() + BRACKET_WIDTH, y + headerSize(i).height());
		if (statements[i].head() != nullptr)
			statements[i].head()->move(p);
		y += headerSize(i).height() + statements[i].height();
	}
}

void Workspace::StatementBrick::setZOrder(int z) {
	Workspace::Brick::setZOrder(z);
	if (statements[0].head() != nullptr)
		statements[0].head()->setZOrder(z + 1);
}

void Workspace::StatementBrick::removeShadow() {
	if (shadow != nullptr) {
		if (next == shadow) {
			Workspace::Brick* next = shadow->next;
			dettach(shadow);
			delete shadow;
			shadow = nullptr;
			attach(next);
			return;
		}

		Workspace::Brick* _next = shadow->next;
		if (_next != nullptr) {
			shadow->dettach(_next);
			removeBrick(shadow);
			insertBrick(_next, shadow_statement_idx);
		} else {
			removeBrick(shadow);
		}
		shadow_statement_idx = -1;
		delete shadow;
		shadow = nullptr;
	}
}

void Workspace::StatementBrick::makeShadow(QPoint pos) {
	if (name == "switch_statement") return;
	QPoint _pos = this->pos();
	QPoint _posBottom = this->pos();
	_posBottom.setY(_posBottom.y() + getHeight());

	int idxLine = 0;
	int y = this->pos().y() + PIN_H;
	int _y = y + headerSize(idxLine).height();
	while (!(y < pos.y() && pos.y() < _y) && idxLine < getLines().count()) {
		y = _y + statements[idxLine].height();
		_y = y + headerSize(idxLine).height();
		idxLine++;
	}

	if (idxLine < statements.count()) {
		if (shadow != nullptr && shadow == statements[idxLine].head()) return;
		if (shadow != nullptr)
			removeShadow();
		shadow = new Shadow(parentWidget());

		shadow_statement_idx = idxLine;
		Workspace::Brick* _oldHead = statements[idxLine].head();
		insertBrick(shadow, shadow_statement_idx);
		shadow->attach(_oldHead);
		return;
	}

	if (shadow != nullptr && shadow == next) return;
	if (shadow != nullptr)
		removeShadow();
	shadow = new Shadow(parentWidget());
	shadow_statement_idx = -1;

	attach(shadow);
}

void Workspace::StatementBrick::replaceShadow(Brick* brick) {
	if (shadow_statement_idx != -1 && statements[shadow_statement_idx].head() == shadow) {
		Workspace::Brick* _oldHead = statements[shadow_statement_idx].head()->next;
		int st_idx = shadow_statement_idx;
		removeShadow();
		insertBrick(brick, st_idx);

		brick->tail()->attach(_oldHead);
		return;
	}

	Workspace::Brick::replaceShadow(brick);
}