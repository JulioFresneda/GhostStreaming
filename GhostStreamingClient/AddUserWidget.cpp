#include "AddUserWidget.h"
#include "servercommunication.h"

AddUserWidget::AddUserWidget(QWidget *parent) : QWidget(parent) {
    ui.setupUi(this);

    connect(ui.addButton, &QPushButton::clicked, this, &AddUserWidget::addButtonClicked);
    connect(ui.cancelButton, &QPushButton::clicked, this, &AddUserWidget::cancelButtonClicked);

}

void AddUserWidget::addButtonClicked(){
    QString text = ui.usernameBox->text();
    std::string username = text.toStdString();
    ServerCommunication::AddUser("http://0.0.0.0:18080/user/create", "bot1", username);
    emit comebackSignal();

}

void AddUserWidget::cancelButtonClicked(){
    emit comebackSignal();

}
