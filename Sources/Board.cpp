#include "Board.h"

#include "Parameter.h"
#include "Shadow.h"
#include "StatementBrick.h"
#include <iostream>

#define X(a, b) b,
const char* v_type_name[] = {
  VALUE_TYPE_TABLE
};
#undef X

Board::Board(QColor bgColor) {
	background = bgColor;
	previewBrick = nullptr;

	QHBoxLayout* hLayout = new QHBoxLayout(this);
	hLayout->setAlignment(Qt::AlignRight);
	QWidget* auxWid = new QWidget(this);
	auxWid->setBaseSize(100, 100);
	QVBoxLayout* vLayout = new QVBoxLayout(auxWid);
	vLayout->setAlignment(Qt::AlignBottom);

	trashCan = new QSvgWidget("D:/Projetos/TCC/ShafraBlock/Assets/trash-close-red.svg", this);
	vLayout->addWidget(trashCan);
	trashCan->setMaximumSize(QSize(60, 60));

	hLayout->addWidget(auxWid);

	setMouseTracking(true);
	setAcceptDrops(true);
	createMainFunction();
}

void Board::createMainFunction() {
	Workspace::StatementBrick* mainfunction = new Workspace::StatementBrick(this, "EXECUTAR %s", "main", QColor("#b35702"));
	mainfunction->move(QPoint(200, 200));
	mainfunction->setZOrder(0);
	mainfunction->show();
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

bool Board::variableExist(QString name) {
	return variables.contains(name);
}

void Board::addVariable(QString name, ValueType type) {
	if (name.isNull() || name.isEmpty()) return;
	variables.insert(name, type);
}

QJsonDocument Board::saveToFile(QString path) {
	if (zOrder.contains(0)) {

		QJsonArray variablesJson;
		for (auto pair : variables.asKeyValueRange()) {
			QJsonObject var;
			var[pair.first] = v_type_name[pair.second];
			variablesJson.append(var);
		}
			

		QJsonArray jsonArray;
		for (QWidget* b : zOrder[0]) {
			Workspace::Brick* brick = ((Workspace::Brick*)b);
			if (brick->isFree()) {
				QJsonObject _json = brick->GetJson();
				jsonArray.append(_json);
			}
		}

		QJsonObject mainJson;
		mainJson["variables"] = variablesJson;
		mainJson["bricks"] = jsonArray;

		QFile file(path);
		QJsonDocument document;
		document.setObject(mainJson) ;
		
		file.open(QFile::WriteOnly | QFile::Text);
		file.write(document.toJson(QJsonDocument::Indented));
		file.close();
		return document;
	}
	return QJsonDocument();
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

void Board::loadTrash(bool open) {
	if (open == trashOpen) return;
	trashOpen = open;
	if (trashOpen)
		trashCan->load(tr("D:/Projetos/TCC/ShafraBlock/Assets/trash-open-red.svg"));
	else
		trashCan->load(tr("D:/Projetos/TCC/ShafraBlock/Assets/trash-close-red.svg"));

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

void Board::deleteBrick(QWidget* widget, int z) {
	zOrder[z].removeAll(widget);
	if (zOrder[z].isEmpty()) {
		zOrder.remove(z);
	};
	delete widget;
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