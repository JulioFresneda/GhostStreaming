#ifndef ADDUSERWIDGET_H
#define ADDUSERWIDGET_H

#include <QWidget>
#include "ui_AddUserWidget.h"

class AddUserWidget : public QWidget {
    Q_OBJECT

public:
    explicit AddUserWidget(QWidget *parent = nullptr);

private:
    Ui::addUserWidget ui;
    void addButtonClicked();
    void cancelButtonClicked();

signals:
    void comebackSignal();
};


#endif // ADDUSERWIDGET_H
