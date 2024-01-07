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

private:
    QLabel *logoLabel;
    QLabel *titleLabel;
    QHBoxLayout *buttonLayout;
    QSequentialAnimationGroup *animationGroup;
    QParallelAnimationGroup *parallelGroup;

    void setupUI();
    void setupAnimations();
    void animateTitleDisappearance();
    void loadUserButtons();
    void animateButtonAppearance(QToolButton *button);
    std::vector<std::string> getUsers();
    void onNewUserClicked();

signals:
    void addUserSignal();

};

#endif // SPLASHSCREEN_H
