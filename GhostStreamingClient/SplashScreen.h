// SplashScreen.h
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QToolButton>
#include <QWidget>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QVBoxLayout>
#include <QTimer>
#include <QPushButton>
#include "servercommunication.h"

class SplashScreen : public QWidget {
    Q_OBJECT

public:
    explicit SplashScreen(QWidget *parent = nullptr);
    void reloadUserButtons();

    std::string userSelected;

private:
    QLabel *logoLabel;
    QLabel *titleLabel;
    QHBoxLayout *buttonLayout;
    QSequentialAnimationGroup *animationGroup;
    QParallelAnimationGroup *parallelGroup;

    QHBoxLayout *buttonsLayout;

    void setupUI();
    void setupAnimations();
    void animateTitleDisappearance();
    void loadUserButtons();


    void animateButtonAppearance(QToolButton *button);

    void onNewUserClicked();
    void userClicked();


signals:
    void addUserSignal();
    void userSelectedSignal();

};

#endif // SPLASHSCREEN_H
