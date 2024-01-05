#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    logoLabel(new QLabel(this)),
    titleLabel(new QLabel(this)),
    buttonLayout(new QHBoxLayout),
    animationGroup(new QSequentialAnimationGroup(this))
{
    setupUI();
    setupAnimations();


}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // Set the size of the main window
    setFixedSize(800, 600);

    // Setup logo label
    QPixmap logoPixmap("/home/juliofgx/GhostStreamingClient/img/logo.png");
    logoPixmap = logoPixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation); // Resize logo
    logoLabel->setPixmap(logoPixmap);
    logoLabel->setGeometry(300, 150, 300, 150); // Adjust geometry as needed



    // Setup title label
    QFont titleFont("moderna", 50); // Adjust the font size as needed
    titleLabel->setFont(titleFont);
    titleLabel->setText("Ghost Streaming");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setGeometry(50, 300, 700, 100); // Adjust geometry as needed
    titleLabel->setStyleSheet("QLabel { color : white; }");


    // ... [rest of the setupUI code]
}


void MainWindow::setupAnimations()
{
    // Opacity animations for logo and title
    QGraphicsOpacityEffect *logoEffect = new QGraphicsOpacityEffect(this);
    logoLabel->setGraphicsEffect(logoEffect);
    QGraphicsOpacityEffect *titleEffect = new QGraphicsOpacityEffect(this);
    titleLabel->setGraphicsEffect(titleEffect);

    QPropertyAnimation *logoOpacityAnimation = new QPropertyAnimation(logoEffect, "opacity");
    logoOpacityAnimation->setDuration(2000); // Adjust duration as needed
    logoOpacityAnimation->setStartValue(0.0);
    logoOpacityAnimation->setEndValue(1.0);

    QPropertyAnimation *titleOpacityAnimation = new QPropertyAnimation(titleEffect, "opacity");
    titleOpacityAnimation->setDuration(2000); // Adjust duration as needed
    titleOpacityAnimation->setStartValue(0.0);
    titleOpacityAnimation->setEndValue(1.0);

    // Parallel animation group for simultaneous animations
    QParallelAnimationGroup *parallelGroup = new QParallelAnimationGroup(this);
    parallelGroup->addAnimation(logoOpacityAnimation);
    parallelGroup->addAnimation(titleOpacityAnimation);

    // Start the animations
    parallelGroup->start();

    // Timer to delay the display of buttons



}




