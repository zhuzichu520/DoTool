#include "MainWindow.h"
#include "qfontdatabase.h"
#include "ScreenImageProvider.h"
#include "ColorFinderController.h"
#include "JsonParserController.h"
#include "ScrcpyController.h"
#include "PhoneController.h"
#include "ItemImage.h"
#include "VideoItem.h"
#include "ItemOpenGL.h"
#include "GlobalStatic.h"
#include <QZXing.h>
#include <QtQml>
#include <QQuickStyle>

MainWindow::MainWindow() {

    QQuickStyle::setStyle("Default");
    QZXing::registerQMLTypes();
    QZXing::registerQMLImageProvider(m_engine);
    m_engine.addImageProvider(QLatin1String("screen"), new ScreenImageProvider);

    QUIHelper *p_uiHelper = uiHelper();
    m_engine.rootContext()->setContextProperty("UIHelper",p_uiHelper);

    qmlRegisterType<ItemImage>("com.dotool.ui", 1, 0, "ItemImage");
    qmlRegisterType<VideoItem>("com.dotool.ui", 1, 0, "VideoItem");
    qmlRegisterType<ItemOpenGL>("com.dotool.ui", 1, 0, "ItemOpenGL");

    qmlRegisterType<ColorFinderController>("com.dotool.controller", 1, 0, "ColorFinderController");
    qmlRegisterType<JsonParserController>("com.dotool.controller", 1, 0, "JsonParserController");
    qmlRegisterType<ScrcpyController>("com.dotool.controller", 1, 0, "ScrcpyController");
    qmlRegisterType<PhoneController>("com.dotool.controller", 1, 0, "PhoneController");

}

MainWindow::~MainWindow() {
}

void MainWindow::show() {
    m_engine.load(QUrl("qrc:/layout/main.qml"));
}
