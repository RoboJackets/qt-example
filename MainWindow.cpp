#include "MainWindow.hpp"

//  note that we call the superclass constructor here and pass on the arguments
MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    _ui.setupUi(this);
}
