#ifndef NEWUSERDIALOG_H
#define NEWUSERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>

class NewUserDialog : public QDialog {
    Q_OBJECT

public:
    NewUserDialog(QWidget *parent = nullptr);

    QString getUserName() const;

private:
    QLineEdit *userNameEdit;
    QPushButton *okButton;
};

#endif // NEWUSERDIALOG_H
