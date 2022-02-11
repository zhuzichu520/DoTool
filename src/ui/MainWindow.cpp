#include "MainWindow.h"
#include "QGuiApplication"
#include "qfontdatabase.h"
#include "ScreenImageProvider.h"
#include "ColorPickerController.h"
#include <QZXing.h>
#include <QZXingImageProvider.h>

MainWindow::MainWindow() {
    QZXing::registerQMLTypes();
    QZXing::registerQMLImageProvider(m_engine);
    m_engine.addImageProvider(QLatin1String("screen"), new ScreenImageProvider);
    qmlRegisterType<ColorPickerController>("com.dotool.controller", 1, 0, "ColorPickerController");
}

MainWindow::~MainWindow() {
}

void MainWindow::show() {
    m_engine.load(QUrl("qrc:/layout/main.qml"));
}
