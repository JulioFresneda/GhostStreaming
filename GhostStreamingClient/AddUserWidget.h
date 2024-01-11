#ifndef ADDUSERWIDGET_H
#define ADDUSERWIDGET_H

#include <QWidget>
#include <QDir>
#include <QScrollArea>
#include "ui_AddUserWidget.h"

class AddUserWidget : public QWidget {
    Q_OBJECT

public:
    explicit AddUserWidget(QWidget *parent = nullptr);

private:
    Ui::addUserWidget ui;
    QString selectedProfilePic;

    void addButtonClicked();
    void cancelButtonClicked();
    void loadImages();
    void imageSelected();

signals:
    void comebackSignal();
    void reloadButtonsSignal();
};


#endif // ADDUSERWIDGET_H
