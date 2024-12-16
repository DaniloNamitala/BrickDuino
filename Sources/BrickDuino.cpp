#include "BrickDuino.h"
#include "Board.h"
#include "ToolboxFunctionBrick.h"
#include "ToolboxStatementBrick.h"
#include "ToolboxValueBrick.h"
#include "Spoiler.h"

BrickDuino::BrickDuino(QWidget* parent) {
    this->_path = "";
    createBlockBoard();
    createBlockToolbox();
    createActions();
    createMenus();
}

void BrickDuino::createActions() {
    saveAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave),tr("&Salvar"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Salvar Projeto"));
    connect(saveAct, &QAction::triggered, this, &BrickDuino::saveFile);

    saveAsAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSaveAs), tr("&Salvar Como"), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Salvar Projeto"));
    connect(saveAsAct, &QAction::triggered, this, &BrickDuino::saveFileAs);
}

void BrickDuino::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&Arquivo"));
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
}

void BrickDuino::saveFile() {
    if (_path.isEmpty())
        return saveFileAs();

    blockBoard->saveToFile(_path);
}

void BrickDuino::saveFileAs() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("Saves (*.json)"));
    dialog.setViewMode(QFileDialog::Detail);
    if (dialog.exec()) {
        _path = dialog.selectedFiles().first();
        if (!_path.endsWith(".json"))
            _path.append(".json");
        blockBoard->saveToFile(_path);
    }
}

void BrickDuino::createBlockBoard() {
    blockBoard = new Board(BOARD_BACKGROUND_COLOR);
    this->setCentralWidget(blockBoard);
}

void BrickDuino::createBlockToolbox() {
    blockToolbox = new QDockWidget(tr("Blocks"), this);
    blockToolbox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    blockToolbox->setMinimumWidth(200);
    blockToolbox->setAllowedAreas(Qt::LeftDockWidgetArea |
                                  Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, blockToolbox);

    QBoxLayout* layout = new QVBoxLayout();
    QScrollArea* scrollArea = new QScrollArea();
    QWidget* w = new QWidget();

    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    w->setLayout(layout);
    scrollArea->setStyleSheet("QScrollArea { border: none; background: #1B1B1B; }");
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(w);
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(0, 0, 0, 0);
    blockToolbox->setWidget(scrollArea); 

    loadBlocksFromJson("D:/Projetos/TCC/BrickDuino/Blocks.json", layout);
}

void BrickDuino::loadBlocksFromJson(const char* path, QLayout* layout) {
    _fileName = path;

    // Opening and reading file content in buffer
    _file.setFileName(_fileName);
    _file.open(QIODevice::ReadOnly | QIODevice::Text);
    _fileBuffer = _file.readAll();
    _file.close();

    // Parsing buffer to json objects
    _document = QJsonDocument::fromJson(_fileBuffer.toUtf8());
    _documentMap = _document.object().toVariantMap();

    // Getting blocks from json
    QVariantList spoilers = _documentMap["spoilers"].toList();
    for (QVariant spoiler : spoilers) {
        QVariantMap spoilerMap = spoiler.toMap();
        QString str_color = spoilerMap["color"].toString();
        Spoiler* s = new Spoiler(spoilerMap["name"].toString(), str_color);
        QColor color = QColor(str_color);

        QVariantList bricks = spoilerMap["bricks"].toList();
        for (QVariant brick : bricks) {
            QVariantMap brickMap = brick.toMap();
            Toolbox::Brick* b = nullptr;
            
            if (brickMap["type"].toString() == "STATEMENT") {
                b = new Toolbox::StatementBrick(brickMap["message"].toString().toStdString().c_str(), brickMap["name"].toString().toStdString().c_str(), color);
            } else if (brickMap["type"].toString() == "FUNCTION") {
                b = new Toolbox::FunctionBrick(brickMap["message"].toString().toStdString().c_str(), brickMap["name"].toString().toStdString().c_str(), color);
            } else if (brickMap["type"].toString() == "VALUE") {
                b = new Toolbox::ValueBrick(brickMap["message"].toString().toStdString().c_str(), brickMap["name"].toString().toStdString().c_str(), color);
            } else if (brickMap["type"].toString() == "LITERAL_VALUE") {
                b = new Toolbox::ValueBrick(brickMap["message"].toString().toStdString().c_str(), brickMap["name"].toString().toStdString().c_str(), color, true);
            }

            QVariantList params = brickMap["args"].toList();
            for (QVariant param : params) {
                QVariantMap paramMap = param.toMap();
                ValueType type = ValueType::ANY;
                QString p_name = paramMap.value("name", tr("undefined")).toString();
                if (paramMap.contains("name"))
                if (paramMap["type"].toString() == "INT") {
                    type = ValueType::INT;
                } else if (paramMap["type"].toString().toUpper() == "FLOAT") {
                    type = ValueType::FLOAT;
                } else if (paramMap["type"].toString().toUpper() == "STRING") {
                    type = ValueType::STRING;
                } else if (paramMap["type"].toString().toUpper() == "BOOL") {
                    type = ValueType::BOOL;
                } else if (paramMap["type"].toString().toUpper() == "LITERAL") {
                    type = ValueType::LITERAL;
                }
                Parameter p(type, p_name);
                b->addParam(p);
            }

            if (b != nullptr)
                s->addWidget(b);
            
        }
        layout->addWidget(s);
    }
}

BrickDuino::~BrickDuino() {}
