#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <QTimer>
#include <QToolButton>

#include "servercommunication.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLabel *logoLabel;
    QLabel *titleLabel;
    QHBoxLayout *buttonLayout;
    QSequentialAnimationGroup *animationGroup;

    void setupUI();
    void setupAnimations();
    void animateTitleDisappear();
    void animateButtonsAppear();
    void loadButtons(int numberOfButtons);
    void animateTitleDisappearance();

    void loadUserButtons();
    void animateButtonAppearance(QToolButton *button);
    std::vector<std::string> getUsers();
};

#endif // MAINWINDOW_H
