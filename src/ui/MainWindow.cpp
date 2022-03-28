#include "MainWindow.h"
#include "qfontdatabase.h"
#include "ScreenImageProvider.h"
#include "ColorFinderController.h"
#include "JsonParserController.h"
#include "ScrcpyController.h"
#include "PhoneController.h"
#include "ScreenCaptureController.h"
#include "ItemImage.h"
#include "VideoItem.h"
#include "ItemOpenGL.h"
#include "GlobalStatic.h"
#include "QLogHelper.h"
#include <QZXing.h>
#include <QtQml>
#include <QQuickStyle>
#include <framelessquickhelper.h>

FRAMELESSHELPER_USE_NAMESPACE

MainWindow::MainWindow(char *argv[]) {

    QGuiApplication::setQuitOnLastWindowClosed(false);
    QFont font;
    font.setFamily("Microsoft YaHei");
    QGuiApplication::setFont(font);
    QGuiApplication::setWindowIcon(QIcon(":/image/ic_logo.png"));
    QQuickStyle::setStyle("Default");
    QZXing::registerQMLTypes();
    QZXing::registerQMLImageProvider(m_engine);
    m_engine.addImageProvider(QLatin1String("screen"), new ScreenImageProvider);

    QUIHelper *p_uiHelper = uiHelper();
//    p_uiHelper->setCode();
    m_engine.rootContext()->setContextProperty("UIHelper",p_uiHelper);

    QLogHelper *p_logHelper = logHelper();
    p_logHelper->initGoogleLog(argv);
    m_engine.rootContext()->setContextProperty("LogHelper",p_logHelper);

    qmlRegisterType<ItemImage>("com.dotool.ui", 1, 0, "ItemImage");
    qmlRegisterType<VideoItem>("com.dotool.ui", 1, 0, "VideoItem");
    qmlRegisterType<ItemOpenGL>("com.dotool.ui", 1, 0, "ItemOpenGL");

    qmlRegisterType<FramelessQuickHelper>("com.dotool.ui", 1, 0, "FramelessHelper");


    qmlRegisterType<ColorFinderController>("com.dotool.controller", 1, 0, "ColorFinderController");
    qmlRegisterType<JsonParserController>("com.dotool.controller", 1, 0, "JsonParserController");
    qmlRegisterType<ScrcpyController>("com.dotool.controller", 1, 0, "ScrcpyController");
    qmlRegisterType<PhoneController>("com.dotool.controller", 1, 0, "PhoneController");
    qmlRegisterType<ScreenCaptureController>("com.dotool.controller", 1, 0, "ScreenCaptureController");

}

MainWindow::~MainWindow() {
}

void MainWindow::show() {
    m_engine.load(QUrl("qrc:/layout/main.qml"));
}
