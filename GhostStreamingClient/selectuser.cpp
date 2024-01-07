#include "selectuser.h"

SelectUser::SelectUser(QWidget *buttonContainer) {
    buttonContainer = buttonContainer;
}


void SelectUser::loadUserButtons() {
    int numberOfUsers = getUsersCount(); // Replace with your actual logic

    for (int i = 0; i < numberOfUsers; ++i) {
        QPushButton *userButton = new QPushButton(QString("User %1").arg(i + 1));
        QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(userButton);
        opacityEffect->setOpacity(0.0); // Start with button invisible
        userButton->setGraphicsEffect(opacityEffect);

        buttonContainer->layout()->addWidget(userButton); // Add to the container

        animateButtonAppearance(userButton);
    }
}


void SelectUser::animateButtonAppearance(QPushButton *button) {
    QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(button->graphicsEffect());
    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(1000); // 1 second to appear
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start();
}

int SelectUser::getUsersCount() {
    // Implement this method to return the actual number of users
    return 5; // Example: 5 users
}
