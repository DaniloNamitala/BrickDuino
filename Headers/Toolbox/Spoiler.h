#pragma once
#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>

class Spoiler : public QWidget {
private:
    QVBoxLayout mainLayout;
    QToolButton toggleButton;
    QWidget contentArea;
    QString title;
public:
    explicit Spoiler(const QString & title = "Teste", QString color = "", QWidget *parent = 0);
    QString getTitle();
    void addWidget(QWidget* widget);
};