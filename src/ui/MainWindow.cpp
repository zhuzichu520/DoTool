#include "MainWindow.h"
#include "QGuiApplication"
#include "qfontdatabase.h"

MainWindow::MainWindow() {
//    int fontId = QFontDatabase::addApplicationFont("qrc:/font/iconfont.ttf");
//    QStringList fontIDs = QFontDatabase::applicationFontFamilies(fontId);
//    if (!fontIDs.isEmpty()) {
//        QFont font(fontIDs.first());
//        QGuiApplication::setFont(font);
//    }
}

MainWindow::~MainWindow() {
}

void MainWindow::show() {
    m_engine.load(QUrl("qrc:/layout/main.qml"));
}
