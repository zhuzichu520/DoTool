#include "MainWindow.h"
#include "QGuiApplication"
#include "qfontdatabase.h"
#include "ScreenImageProvider.h"
#include "ColorPickerController.h"

MainWindow::MainWindow() {
    m_engine.addImageProvider(QLatin1String("screen"), new ScreenImageProvider);
    qmlRegisterType<ColorPickerController>("com.dotool.controller", 1, 0, "ColorPickerController");
}

MainWindow::~MainWindow() {
}

void MainWindow::show() {
    m_engine.load(QUrl("qrc:/layout/main.qml"));
}
