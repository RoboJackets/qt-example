#include "MainWindow.hpp"

//  note that we call the superclass constructor here and pass on the arguments
MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    _ui.setupUi(this);

    QObject::connect(_ui.button, &QPushButton::clicked, this, &MainWindow::buttonClicked);
}

void MainWindow::buttonClicked() {
    QString text = _ui.textField->text();
    _ui.listWidget->addItem(text);
}

