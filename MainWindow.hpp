
//  put "#pragma once" at the top of header files to protect against being included multiple times
#pragma once

#include <QtWidgets>
#include "ui_MainWindow.h"


class MainWindow : public QMainWindow {
public:
    //  override the constructor
    MainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);

    void buttonClicked();

    Ui_MainWindow _ui;
};
