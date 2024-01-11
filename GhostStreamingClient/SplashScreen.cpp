// SplashScreen.cpp
#include "SplashScreen.h"

SplashScreen::SplashScreen(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupAnimations();
}

void SplashScreen::setupUI() {
    // Set up logo and title similar to your current setupUI method
    logoLabel = new QLabel(this);
    titleLabel = new QLabel(this);
    QPixmap logoPixmap("/home/juliofgx/CLionProjects/GhostStreaming/img/logo.png");
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
}

void SplashScreen::setupAnimations() {
    // Set up animations similar to your current setupAnimations method
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
    parallelGroup = new QParallelAnimationGroup(this);
    parallelGroup->addAnimation(logoOpacityAnimation);
    parallelGroup->addAnimation(titleOpacityAnimation);


    // Start the animations
    parallelGroup->start();

    connect(parallelGroup, &QParallelAnimationGroup::finished, this, &SplashScreen::animateTitleDisappearance);

}


void SplashScreen::animateTitleDisappearance() {
    qDebug() << "Animating title disappearance";

    QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(titleLabel->graphicsEffect());
    if (!effect) {
        qDebug() << "Title label does not have an opacity effect";
        return;
    }

    effect->setOpacity(1.0); // Ensure starting opacity is 1

    QPropertyAnimation *titleFadeOut = new QPropertyAnimation(effect, "opacity", this);
    titleFadeOut->setDuration(1000); // 1 second for title fade out
    titleFadeOut->setStartValue(1.0);
    titleFadeOut->setEndValue(0.0);

    connect(titleFadeOut, &QPropertyAnimation::finished, this, [=]() {
        // Delay of 1 second before starting button animations
        QTimer::singleShot(1000, this, &SplashScreen::loadUserButtons);
    });

    titleFadeOut->start();
}

void SplashScreen::animateButtonAppearance(QToolButton *button) {
    QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(button->graphicsEffect());
    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(1000); // 1 second to appear
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start();
}

void SplashScreen::loadUserButtons() {
    qDebug() << "Loading user buttons";

    std::vector<std::string> userList;
    std::vector<std::string> profilePics;

    ServerCommunication::GetUsers("http://0.0.0.0:18080/user/list","bot1", userList, profilePics);

     // Replace with your actual logic
    userList.push_back("newuser");
    profilePics.push_back("newuser.png");

    int buttonSize = 50; // Fixed size for square buttons
    int iconSize = 50; // Size of the icon
    int textHeight = 20; // Height allocated for text

    QWidget *buttonContainer = new QWidget(this);
    buttonsLayout = new QHBoxLayout(buttonContainer);
    buttonContainer->setLayout(buttonsLayout);

    qDebug() << "Iterating user buttons";

    for (int i = 0; i < userList.size(); ++i) {

        QToolButton *userButton = new QToolButton(buttonContainer);
        userButton->setIcon(QIcon(("/home/juliofgx/CLionProjects/GhostStreaming/GhostStreamingClient/img/" + profilePics[i]).c_str())); // Set the image
        userButton->setIconSize(QSize(iconSize, iconSize)); // Set the icon size
        userButton->setText(QString(userList[i].c_str()));
        userButton->setFixedSize(buttonSize, buttonSize+textHeight); // Adjust size for icon + text
        userButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        // Style the button
        userButton->setStyleSheet("QToolButton { text-align: center; border: none; background-color: transparent; }");

        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(userButton);
        opacityEffect->setOpacity(0.0); // Start with button invisible
        userButton->setGraphicsEffect(opacityEffect);

        buttonsLayout->addWidget(userButton); // Add to the container layout

        animateButtonAppearance(userButton);
        qDebug() << "Added button for User" << i + 1;

        if(userList[i] == "newuser"){
            connect(userButton, &QPushButton::clicked, this, &SplashScreen::onNewUserClicked);
        }
        else{
            userSelected = userList[i];
            connect(userButton, &QPushButton::clicked, this, &SplashScreen::userClicked);
        }
    }

    // Set the geometry or position of buttonContainer appropriately
    // For example, if titleLabel was at (x, y, width, height):
    buttonContainer->setGeometry(50, 300, 700, 100);

    // If using layouts to manage positions, add buttonContainer to the main layout
    // where titleLabel was located. Example:
    // mainLayout->addWidget(buttonContainer);

    buttonContainer->show(); // Make sure it's visible
}

void clearLayout(QLayout *layout) {
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        } else if (QLayout *childLayout = item->layout()) {
            clearLayout(childLayout);
        }
        delete item;
    }
}

void SplashScreen::reloadUserButtons(){
    clearLayout(buttonsLayout);
    loadUserButtons();
}

void SplashScreen::userClicked() {
    qDebug() << "Add User button clicked";
    emit userSelectedSignal();
}



void SplashScreen::onNewUserClicked() {
    qDebug() << "User button clicked:" << userSelected;
    emit addUserSignal();
}
