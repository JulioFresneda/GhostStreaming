#include "newuserdialog.h"

NewUserDialog::NewUserDialog(QWidget *parent) : QDialog(parent) {
    userNameEdit = new QLineEdit(this);
    okButton = new QPushButton("OK", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(userNameEdit);
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, this, &NewUserDialog::accept);
}

QString NewUserDialog::getUserName() const {
    return userNameEdit->text();
}
