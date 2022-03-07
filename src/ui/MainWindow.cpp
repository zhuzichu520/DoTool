#include "MainWindow.h"
#include "qfontdatabase.h"
#include "ScreenImageProvider.h"
#include "ColorFinderController.h"
#include "JsonParserController.h"
#include "ItemImage.h"
#include "GlobalStatic.h"
#include <QZXing.h>
#include <QtQml>

MainWindow::MainWindow() {

    QZXing::registerQMLTypes();
    QZXing::registerQMLImageProvider(m_engine);
    m_engine.addImageProvider(QLatin1String("screen"), new ScreenImageProvider);

    QUIHelper *p_uiHelper = uiHelper();
    m_engine.rootContext()->setContextProperty("UIHelper",p_uiHelper);

    qmlRegisterType<ItemImage>("com.dotool.ui", 1, 0, "ItemImage");

    qmlRegisterType<ColorFinderController>("com.dotool.controller", 1, 0, "ColorFinderController");
    qmlRegisterType<JsonParserController>("com.dotool.controller", 1, 0, "JsonParserController");

}

MainWindow::~MainWindow() {
}

void MainWindow::show() {
    m_engine.load(QUrl("qrc:/layout/main.qml"));
}
