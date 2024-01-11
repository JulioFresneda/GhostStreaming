#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    logoLabel(new QLabel(this)),
    titleLabel(new QLabel(this)),
    buttonLayout(new QHBoxLayout),
    animationGroup(new QSequentialAnimationGroup(this))


{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    splashScreen = new SplashScreen(this);
    addUserWidget = new AddUserWidget(this);

    stackedWidget->addWidget(splashScreen);
    stackedWidget->addWidget(addUserWidget);

    // Set SplashScreen as the initial view
    stackedWidget->setCurrentWidget(splashScreen);

    connect(splashScreen, &SplashScreen::addUserSignal, this, &MainWindow::loadAddUserUI);
    connect(splashScreen, &SplashScreen::userSelectedSignal, this, &MainWindow::loadStreamingWindow);

    connect(addUserWidget, &AddUserWidget::comebackSignal, this, &MainWindow::loadMainWindow);
    connect(addUserWidget, &AddUserWidget::reloadButtonsSignal, this, &MainWindow::reloadMainWindow);







}

MainWindow::~MainWindow()
{
}

void MainWindow::loadAddUserUI(){
    qDebug() << "Load Add User UI";
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::loadMainWindow(){
    qDebug() << "Load main window";

    stackedWidget->setCurrentIndex(0);
}

void MainWindow::reloadMainWindow(){
    qDebug() << "Reload main window";
    splashScreen->reloadUserButtons();
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::loadStreamingWindow(){
    QWidget* currentCentralWidget = this->centralWidget();
    if (currentCentralWidget != nullptr) {
        currentCentralWidget->deleteLater(); // or this->takeCentralWidget();
    }

    StreamingWindow* newContent = new StreamingWindow(this);
    this->setCentralWidget(newContent);


}










