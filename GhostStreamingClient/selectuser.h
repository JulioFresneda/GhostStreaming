#ifndef SELECTUSER_H
#define SELECTUSER_H

#import <QPushButton>
#import <QGraphicsOpacityEffect>
#import <QPropertyAnimation>
#import <QWidget>
#import <QVBoxLayout>


class SelectUser
{
public:
    SelectUser(QWidget *buttonContainer);
    void loadUserButtons();
    void animateButtonAppearance(QPushButton *button);
    int getUsersCount();
private:
    QWidget *buttonContainer;
};

#endif // SELECTUSER_H
