#include "BrickDuino.h"
#include "Board.h"
#include "ToolboxFunctionBrick.h"
#include "ToolboxStatementBrick.h"
#include "ToolboxValueBrick.h"
#include "Spoiler.h"

BrickDuino::BrickDuino(QWidget* parent) {
    crteateBlockBoard();
    crteateBlockToolbox();
}

void BrickDuino::crteateBlockBoard() {
    blockBoard = new Board(BOARD_BACKGROUND_COLOR);
    this->setCentralWidget(blockBoard);
}

void BrickDuino::crteateBlockToolbox() {
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
                b = new Toolbox::StatementBrick(brickMap["message"].toString().toStdString().c_str(), color);
            } else if (brickMap["type"].toString() == "FUNCTION") {
                b = new Toolbox::FunctionBrick(brickMap["message"].toString().toStdString().c_str(), color);
            } else if (brickMap["type"].toString() == "VALUE" || brickMap["type"].toString() == "BINARY_OPERATOR") {
                b = new Toolbox::ValueBrick(brickMap["message"].toString().toStdString().c_str(), color, brickMap["type"].toString() == "BINARY_OPERATOR");
            }

            QVariantList params = brickMap["args"].toList();
            for (QVariant param : params) {
                QVariantMap paramMap = param.toMap();
                ValueType type = ValueType::ANY;
                if (paramMap["type"].toString() == "INT") {
                    type = ValueType::INT;
                } else if (paramMap["type"].toString() == "FLOAT") {
                    type = ValueType::FLOAT;
                } else if (paramMap["type"].toString() == "STRING") {
                    type = ValueType::STRING;
                } else if (paramMap["type"].toString() == "BOOL") {
                    type = ValueType::BOOL;
                }
                Parameter p(type);
                b->addParam(p);
            }

            if (b != nullptr)
                s->addWidget(b);
            
        }
        layout->addWidget(s);
    }
}

BrickDuino::~BrickDuino() {}
