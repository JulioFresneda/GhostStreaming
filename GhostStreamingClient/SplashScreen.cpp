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

    std::vector<std::string> users = getUsers(); // Replace with your actual logic
    users.push_back("newuser");

    int buttonSize = 50; // Fixed size for square buttons
    int iconSize = 50; // Size of the icon
    int textHeight = 20; // Height allocated for text

    QWidget *buttonContainer = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(buttonContainer);
    buttonContainer->setLayout(layout);

    qDebug() << "Iterating user buttons";

    for (int i = 0; i < users.size(); ++i) {

        QToolButton *userButton = new QToolButton(buttonContainer);        userButton->setIcon(QIcon(("/home/juliofgx/CLionProjects/GhostStreaming/GhostStreamingClient/img/" + users[i] + ".png").c_str())); // Set the image
        userButton->setIconSize(QSize(iconSize, iconSize)); // Set the icon size
        userButton->setText(QString(users[i].c_str()));
        userButton->setFixedSize(buttonSize, buttonSize+textHeight); // Adjust size for icon + text
        userButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        // Style the button
        userButton->setStyleSheet("QToolButton { text-align: center; border: none; background-color: transparent; }");

        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(userButton);
        opacityEffect->setOpacity(0.0); // Start with button invisible
        userButton->setGraphicsEffect(opacityEffect);

        layout->addWidget(userButton); // Add to the container layout

        animateButtonAppearance(userButton);
        qDebug() << "Added button for User" << i + 1;

        if(users[i] == "newuser"){
            connect(userButton, &QPushButton::clicked, this, &SplashScreen::onNewUserClicked);
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

std::vector<std::string> SplashScreen::getUsers() {
    // Implement this method to return the actual number of users
    std::vector<std::string> user_list = ServerCommunication::GetUsers("http://0.0.0.0:18080/user/list","bot1");
    return user_list;

}

void SplashScreen::onNewUserClicked() {
    qDebug() << "Add User button clicked";
    emit addUserSignal();
}
