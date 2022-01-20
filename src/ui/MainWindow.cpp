#include "MainWindow.h"

MainWindow::MainWindow() {

}

MainWindow::~MainWindow() {
}

void MainWindow::show() {
    m_engine.load(QUrl("qrc:/layout/main.qml"));
}
