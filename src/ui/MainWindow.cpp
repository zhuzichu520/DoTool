#include "MainWindow.h"
#include "qfontdatabase.h"
#include "ScreenImageProvider.h"
#include "ColorPickerController.h"
#include "JsonParserController.h"
#include "ItemImage.h"
#include "QUIHelper.h"
#include <QZXing.h>
#include <QtQml>

MainWindow::MainWindow() {

    m_engine.addImportPath(QStringLiteral("qrc:/components/"));

    for(QString path : m_engine.importPathList())
        qDebug() << path;

    QZXing::registerQMLTypes();
    QZXing::registerQMLImageProvider(m_engine);
    m_engine.addImageProvider(QLatin1String("screen"), new ScreenImageProvider);

    m_engine.rootContext()->setContextProperty("UIHelper", new QUIHelper);

    qmlRegisterType<ItemImage>("com.dotool.ui", 1, 0, "ItemImage");

    qmlRegisterType<ColorPickerController>("com.dotool.controller", 1, 0, "ColorPickerController");
    qmlRegisterType<JsonParserController>("com.dotool.controller", 1, 0, "JsonParserController");



}

MainWindow::~MainWindow() {
}

void MainWindow::show() {
    m_engine.load(QUrl("qrc:/layout/main.qml"));
}
