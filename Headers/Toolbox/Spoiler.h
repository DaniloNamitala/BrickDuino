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
    QColor color;
    QVBoxLayout* buttonLayout;
public:
    explicit Spoiler(const QString & title = "Teste", QString color = "", QWidget *parent = 0);
    QString getTitle();
    QColor getColor();
    void addWidget(QWidget* widget);
    void addActionButton(QWidget* widget);
};