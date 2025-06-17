#include "BrickDuino.h"
#include "Board.h"
#include "ToolboxFunctionBrick.h"
#include "ToolboxStatementBrick.h"
#include "ToolboxValueBrick.h"
#include "Spoiler.h"
#include "Compiler.h"
#include "ModalNewVariable.h"

BrickDuino::BrickDuino(QWidget* parent) {
    this->_path = "";
    spoilerMap = QMap<QString, Spoiler*>();
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

    compileCpp = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart), tr("&C++"), this);
    compileCpp->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_C);
    compileCpp->setStatusTip(tr("Compilar C++"));
    connect(compileCpp, &QAction::triggered, this, [=]() {
        compileProject(".cpp", "cpp_grammar");
     });

    compilePas = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart), tr("&Pascal"), this);
    compilePas->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_P);
    compilePas->setStatusTip(tr("Compilar Pascal"));
    connect(compilePas, &QAction::triggered, this, [=](){
        compileProject(".pas", "pascal_grammar");
    });

    compilePy = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart), tr("&Python"), this);
    compilePy->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_P);
    compilePy->setStatusTip(tr("Compilar Python"));
    connect(compilePy, &QAction::triggered, this, [=]() {
        compileProject(".py", "python_grammar");
    });
}

void BrickDuino::compileProject(QString extension, QString grammar) {
    saveFile();
    QString fullpath = _path + extension;
    Compiler compiler(_document,fullpath, grammar);
    compiler.compile();
    system(("notepad " + fullpath).toStdString().c_str());
}

void BrickDuino::modalCreateVariable() {
    ModalNewVariable* modal = new ModalNewVariable(this);
    if (modal->exec()) {
        createVariable(modal->getText(), modal->getType());
    }
    delete modal;
}

void BrickDuino::createVariable(QString name, QString type) {

    if (blockBoard->variableExist(name)) {
        QMessageBox::warning(this, "Erro", "Ja existe uma variavel com este nome!!");
        return;
    }

    Spoiler* spoiler = spoilerMap.value("VARIAVEIS", nullptr);
    if (spoiler != nullptr) {
        Toolbox::ValueBrick* b = new Toolbox::ValueBrick(name.toStdString().c_str(), "variable_call", spoiler->getColor());
        ValueType _type = b->setType(type);
        blockBoard->addVariable(name, _type);
        spoiler->addWidget(b);
    }
}

void BrickDuino::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&Arquivo"));
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);

    compileMenu = menuBar()->addMenu(tr("&Compilar"));
    compileMenu->addAction(compileCpp);
    compileMenu->addAction(compilePas);
    compileMenu->addAction(compilePy);
}

void BrickDuino::saveFile() {
    if (_path.isEmpty())
        return saveFileAs();

    _document = blockBoard->saveToFile(_path);
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
        _document = blockBoard->saveToFile(_path);
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
    addSpoilerActions();
}

void BrickDuino::addSpoilerActions() {
    Spoiler* _spoiler = spoilerMap.value("VARIAVEIS", nullptr);
    if (_spoiler != nullptr) {
        QPushButton* addVariable = new QPushButton("Criar Variável");
        addVariable->setCursor(Qt::PointingHandCursor);
        addVariable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        connect(addVariable, &QPushButton::clicked, this, &BrickDuino::modalCreateVariable);
        _spoiler->addActionButton(addVariable);
    }
}

void BrickDuino::loadBlocksFromJson(const char* path, QLayout* layout) {

    // Opening and reading file content in buffer
    QFile file;
    QString fileBuffer;
    file.setFileName(tr(path));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileBuffer = file.readAll();
    file.close();

    // Parsing buffer to json objects
    QJsonDocument document = QJsonDocument::fromJson(fileBuffer.toUtf8());
    QVariantMap documentMap = document.object().toVariantMap();

    // Getting blocks from json
    QVariantList spoilers = documentMap["spoilers"].toList();
    for (QVariant spoiler : spoilers) {
        QVariantMap _spoilerMap = spoiler.toMap();
        QString str_color = _spoilerMap["color"].toString();
        Spoiler* s = new Spoiler(_spoilerMap["name"].toString(), str_color);
        QColor color = QColor(str_color);

        QVariantList bricks = _spoilerMap["bricks"].toList();
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
        spoilerMap[s->getTitle()] = s;
        layout->addWidget(s);
    }
}

BrickDuino::~BrickDuino() {}
