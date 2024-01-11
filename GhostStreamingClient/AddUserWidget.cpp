#include "AddUserWidget.h"
#include "servercommunication.h"

AddUserWidget::AddUserWidget(QWidget *parent) : QWidget(parent) {
    ui.setupUi(this);
    loadImages();
    connect(ui.addButton, &QPushButton::clicked, this, &AddUserWidget::addButtonClicked);
    connect(ui.cancelButton, &QPushButton::clicked, this, &AddUserWidget::cancelButtonClicked);

}

void AddUserWidget::addButtonClicked(){
    QString text = ui.usernameBox->text();
    std::string username = text.toStdString();
    ServerCommunication::AddUser("http://0.0.0.0:18080/user/create", "bot1", username, selectedProfilePic.toStdString());
    emit reloadButtonsSignal();
    emit comebackSignal();

}

void AddUserWidget::cancelButtonClicked(){
    emit comebackSignal();

}

void AddUserWidget::loadImages() {
    QDir directory("/home/juliofgx/CLionProjects/GhostStreaming/GhostStreamingClient/img");
    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.png", QDir::Files);
    QGridLayout *layout = ui.gridLayout;
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSpacing(2); // Replace 2 with the desired spacing in pixels
    layout->setContentsMargins(120, 150, 120, 50); // Top, right, bottom, left margins in pixels


    int row = 0;
    int column = 0;
    const int maxColumn = 4;  // Maximum number of columns



    foreach(QString filename, images) {
        if (column > maxColumn) {
            column = 0;
            row++;
        }

        QString filePath = directory.filePath(filename);
        QPushButton *imageButton = new QPushButton;
        imageButton->setIcon(QIcon(filePath));
        imageButton->setIconSize(QSize(100, 100));
        imageButton->setFixedSize(imageButton->iconSize() + QSize(10, 10));
        //imageButton->setStyleSheet("QPushButton { border: none; background-color: transparent; }");

        imageButton->setProperty("imageName", filename);

        layout->addWidget(imageButton, row, column++);

        connect(imageButton, &QPushButton::clicked, this, &AddUserWidget::imageSelected);
    }

    layout->setAlignment(Qt::AlignCenter); // Aligns the grid layout to the center

    QScrollArea *scrollArea = ui.scrollArea;
    QWidget *containerWidget = new QWidget;
    containerWidget->setLayout(layout);
    scrollArea->setWidget(containerWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Disable horizontal scroll bar
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //setLayout(layout);
}



void AddUserWidget::imageSelected() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString selectedImagePath = button->property("imageName").toString(); // Store the selected image path
        qDebug() << selectedImagePath;
        selectedProfilePic = selectedImagePath;

    }
}

