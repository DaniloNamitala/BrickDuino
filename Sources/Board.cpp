#include "Board.h"

#include "Parameter.h"
#include "Shadow.h"
#include <iostream>


Board::Board(QColor bgColor) {
	background = bgColor;
	previewBrick = nullptr;
	setMouseTracking(true);
	setAcceptDrops(true);
}

void Board::paintEvent(QPaintEvent* event) {
	painter.begin(this);
	painter.fillRect(event->rect(), background);
	painter.end();
}

void Board::removeOrder(QWidget* widget, int z_order) {
	if (zOrder.contains(z_order)) {
		zOrder[z_order].removeAll(widget);
	}
}

void Board::dragLeaveEvent(QDragLeaveEvent* event) {
	delete previewBrick;
	previewBrick = nullptr;
}

void Board::saveToFile(QString path) {
	if (zOrder.contains(0)) {

		QJsonArray jsonArray;
		for (QWidget* b : zOrder[0]) {
			Workspace::Brick* brick = ((Workspace::Brick*)b);
			if (brick->isFree()) {
				QJsonObject _json = brick->GetJson();
				jsonArray.append(_json);
			}
		}

		QFile file(path);
		QJsonParseError jsonParser;
		QJsonDocument document;
		document.setArray(jsonArray);
		
		file.open(QFile::WriteOnly | QFile::Text);
		file.write(document.toJson(QJsonDocument::Indented));
		file.close();
	}
}

void Board::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasFormat("application/x-brick") && previewBrick == nullptr) {
		QByteArray data = event->mimeData()->data("application/x-brick");
		QDataStream stream(&data, QIODevice::ReadOnly);
		stream >> previewBrick;
		previewBrick->setParent(this);
		previewBrick->move(event->pos());
		previewBrick->show();
		event->acceptProposedAction();
	}
}

void Board::dragMoveEvent(QDragMoveEvent* event)
{
	if (previewBrick) {
		previewBrick->moveBrick(event->pos());
		event->accept();
	}
}


void Board::dropEvent(QDropEvent* event)
{
	if (previewBrick == nullptr) return;

	previewBrick->mouseReleaseEvent(nullptr);
	previewBrick = nullptr;
	event->acceptProposedAction();
}


void Board::setZOrder(QWidget* widget, int old_z, int new_z) {
	if (old_z == new_z) return;

	if (zOrder.contains(old_z)) {
		zOrder[old_z].removeAll(widget);
		if (zOrder[old_z].isEmpty())
			zOrder.remove(old_z);
	}

	if (!zOrder.contains(new_z)) zOrder[new_z] = QList<QWidget*>();
	zOrder[new_z].append(widget);

	QMapIterator<int, QList<QWidget*>> i(zOrder);
	while (i.hasNext()) {
		i.next();
		for (QWidget* w : i.value()) {
			w->raise();
		}
	}
}

Board::~Board() {
	QMapIterator<int, QList<QWidget*>> i(zOrder);
	while (i.hasNext()) {
		i.next();
		for (QWidget* w : i.value()) {
			delete w;
		}
	}
}