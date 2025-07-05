#pragma once

#include <QtCore>
#include <QJsonDocument>

class Compiler {
private:
	QJsonDocument document;
	QString path;
	bool isPascal = false;
	QMap<QString, QString> grammar;

	void writeBrick(QTextStream &stream, QVariantMap bMap, QString tab);
	void write(QTextStream &stream, QVariantMap bMap, QString tab);
	void writeIf(QTextStream &stream, QVariantMap bMap, QString tab);
	void writeCase(QTextStream &stream, QVariantMap bMap, QString tab);
	void readGrammar(QString path);
	QString getValue(QVariantMap map, QString &valueType);
	void writeVariables(QTextStream& stream);
public:
	Compiler(QJsonDocument document, QString output, QString grammar);
	bool compile();
};