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
#include <QStackedWidget>

#include "AddUserWidget.h"
#include "ui_mainwindow.h"

#include "SplashScreen.h"
#include "streamingwindow.h"

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
    Ui::MainWindow *ui;

    SplashScreen* splashScreen;
    AddUserWidget* addUserWidget;


    QStackedWidget *stackedWidget;




    void setupUI();
    void setupAnimations();
    void animateTitleDisappear();
    void animateButtonsAppear();
    void loadButtons(int numberOfButtons);
    void animateTitleDisappearance();

    void loadUserButtons();
    void animateButtonAppearance(QToolButton *button);
    std::vector<std::string> getUsers();

    void onNewUserClicked();

    void loadAddUserUI();
    void loadMainWindow();
    void reloadMainWindow();
    void loadStreamingWindow();
};

#endif // MAINWINDOW_H
