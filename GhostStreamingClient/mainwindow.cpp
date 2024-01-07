#include "mainwindow.h"
#include "AddUserWidget.h"
#include "SplashScreen.h"


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

    SplashScreen* splashScreen = new SplashScreen(this);
    AddUserWidget* addUserWidget = new AddUserWidget(this);

    stackedWidget->addWidget(splashScreen);
    stackedWidget->addWidget(addUserWidget);

    // Set SplashScreen as the initial view
    stackedWidget->setCurrentWidget(splashScreen);

    connect(splashScreen, &SplashScreen::addUserSignal, this, &MainWindow::loadAddUserUI);
    connect(addUserWidget, &AddUserWidget::comebackSignal, this, &MainWindow::loadMainWindow);







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










