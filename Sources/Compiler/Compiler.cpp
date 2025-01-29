#include "Compiler.h"
#include <QtCore>

Compiler::Compiler(QJsonDocument document, QString output) {
	this->document = document;
	this->path = output;

	readGrammar("D:/Projetos/TCC/BrickDuino/Sources/cpp_grammar.json");
}

bool Compiler::compile() {
	QFile out(path);
	out.open(QFile::WriteOnly | QFile::Text);
	QTextStream stream(&out);

	if (grammar.contains("includes")) {
		stream << grammar["includes"];
	}

	writeVariables(stream);

	QVariantList bricks = document["bricks"].toArray().toVariantList();
	for (QVariant brick : bricks) {
		QVariantMap bMap = brick.toMap();
		writeBrick(stream, bMap, "");
	}
	return true;
}

void Compiler::writeVariables(QTextStream& stream) {
	QVariantList variables = document["variables"].toArray().toVariantList();

	for (QVariant var : variables) {
		QJsonObject obj = var.toJsonObject();
		QString name = obj.keys().first();
		QString type = obj.value(name).toString().toLower();

		stream << type << " " << name << ";\n";
	}
	stream << "\n";
}

void Compiler::writeCase(QTextStream& stream, QVariantMap bMap, QString tab) {
	QString message = bMap.value("message", "").toString();
	QStringList lines = message.split("%s");
	lines.removeAll("");
	QString name = bMap.value("name", "").toString();
	QString type = bMap.value("type", "").toString();

	QVariantList statements = bMap["statements"].toList();
	QVariantList args = bMap["args"].toList();

	QRegularExpression re("%[0-9]+");

	for (int i = 0; i < lines.size(); i++) {
		QString _tab = " ";
		QString line = lines.at(i);
		QRegularExpressionMatch match = re.match(line);

		QString code = grammar["case_statement"];
		if (i == lines.count() - 1)
			code = grammar["default_statement"];
		if (match.hasMatch()) {
			QString strMatch = match.captured();
			int pos = strMatch.mid(1).toInt() - 1;
			if (args.size() > pos) {
				QString arg = getValue(args[pos].toMap()["value"].toMap());
				code.replace("[args]", arg);
			}
		}
		QStringList c = code.split("statement");
		stream << tab << (c[0]);
		if (statements.size() > i) {
			QVariantMap head = statements[i].toMap()["head"].toMap();
			writeBrick(stream, head, tab + "\t");
		}
		else {
			stream << "\n";
		}
		stream << tab << c.value(1, "").trimmed() << "\n";
	}
	stream << "\n";
}

void Compiler::writeIf(QTextStream& stream, QVariantMap bMap, QString tab) {

	QString message = bMap.value("message", "").toString();
	QStringList lines = message.split("%s");
	lines.removeAll("");
	QString name = bMap.value("name", "").toString();
	QString type = bMap.value("type", "").toString();

	QVariantList statements = bMap["statements"].toList();
	QVariantList args = bMap["args"].toList();

	QRegularExpression re("%[0-9]+");

	for (int i = 0; i < lines.size(); i++) {
		QString _tab = " ";
		QString line = lines.at(i);
		QRegularExpressionMatch match = re.match(line);


		QString code = grammar["else_statement"];
		if (match.hasMatch()) {
			code = grammar["else_if_statement"];
			if (i == 0) {
				code = grammar["if_statement"];
				_tab = tab;
			}
			QString strMatch = match.captured();
			int pos = strMatch.mid(1).toInt() - 1;
			if (args.size() > pos) {
				QString arg = getValue(args[pos].toMap()["value"].toMap());
				code.replace("[args]", arg);
			}
		}
		QStringList c = code.split("statement");
		stream << _tab << (c[0]);
		if (statements.size() > i) {
			QVariantMap head = statements[i].toMap()["head"].toMap();
			writeBrick(stream, head, tab + "\t");
		}
		else {
			stream << "\n";
		}
		stream << tab << c.value(1, "").trimmed();

	}
	stream << "\n";
}

void Compiler::write(QTextStream& stream, QVariantMap bMap, QString tab) {
	QString message = bMap.value("message", "").toString();
	QString name = bMap.value("name", "").toString();
	QString type = bMap.value("type", "").toString();
	QString variable = bMap.value("variable", "").toString();

	QVariantList statements = bMap["statements"].toList();
	QVariantList args = bMap["args"].toList();

	QRegularExpression re("%[0-9]+");
	QRegularExpressionMatchIterator it = re.globalMatch(message);
	QString code = grammar[name];

	if (code.contains("%v0"))
		code.replace("%v0", variable);

	while (it.hasNext()) {
		QRegularExpressionMatch match = it.next();
		QString strMatch = match.captured();
		int pos = strMatch.mid(1).toInt() - 1;
		if (args.size() > pos) {
			QString arg = getValue(args[pos].toMap()["value"].toMap());
			code.replace(strMatch, arg);
		}
	}
	QStringList c = code.split("statement");
	stream << tab << (c[0]);
	if (statements.size() > 0) {
		QVariantMap head = statements[0].toMap()["head"].toMap();
		writeBrick(stream, head, tab + "\t");
	}
	if (c.size() > 1)
		stream << tab << c.value(1, "").trimmed();
	stream << "\n";
}


void Compiler::writeBrick(QTextStream& stream, QVariantMap bMap, QString tab) {
	QString type = bMap.value("type", "").toString();
	QString name = bMap.value("name", "").toString();
	QString message = bMap.value("message", "").toString();


	if (type == "VALUE" || type == "LITERAL_VALUE")
		stream << getValue(bMap) << "\n";
	else if (name == "if_statement")
		writeIf(stream, bMap, tab);
	else if (name == "case_statement")
		writeCase(stream, bMap, tab);
	else {
		write(stream, bMap, tab);
	}

	if (bMap.contains("chain")) {
		QVariantList chain = bMap["chain"].toList();
		for (QVariant c : chain) {
			writeBrick(stream, c.toMap(), tab);
		}
	}
}

void Compiler::readGrammar(const char* path) {
	QFile file;
	QString fileBuffer;
	file.setFileName(QString(path));
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	fileBuffer = file.readAll();
	file.close();

	QJsonDocument document = QJsonDocument::fromJson(fileBuffer.toUtf8());
	QVariantMap documentMap = document.object().toVariantMap();

	for (QString key : documentMap.keys()) {
		grammar[key] = documentMap[key].toString();
	}
}

QString Compiler::getValue(QVariantMap map) {
	QString name = map["name"].toString();
	QString message = map["message"].toString();

	if (name == "literal_number") return message;
	if (name == "literal_string") return "\"" + message + "\"";
	if (name == "variable_call") return message;

	QVariantList args = map["args"].toList();
	if (grammar.contains(name)) {
		QString code = grammar[name];
		QRegularExpression re("%[0-9]+");
		QRegularExpressionMatchIterator i = re.globalMatch(code);
		while (i.hasNext()) {
			QString match = i.next().captured();
			int pos = match.mid(1).toInt() - 1;
			if (args.size() > pos) {
				QString arg = getValue(args[pos].toMap()["value"].toMap());
				code.replace(match, arg);
			}
		}		return code;
	}
	else {
		return "";
	}
}