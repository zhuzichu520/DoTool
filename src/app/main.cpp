#include <QGuiApplication>
#include <QtQuick/qquickwindow.h>
#include "MainWindow.h"
#include <QFont>
#include <QtWebEngine>


int main(int argc, char *argv[])
{
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#endif
//    QGuiApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
//    QQuickWindow::setSceneGraphBackend(QSGRendererInterface::Software);
    QtWebEngine::initialize();
    QGuiApplication::setApplicationName("DoTool");
    QGuiApplication::setOrganizationName("DoTool");
    QGuiApplication::setOrganizationDomain("https://github.com/zhuzichu520/DoTool");
    QGuiApplication::setApplicationVersion("1.0");
    QGuiApplication app(argc, argv);
    QFont font;
    font.setFamily("Microsoft YaHei");
    app.setFont(font);

    MainWindow window;
    window.show();
    QGuiApplication::exec();
    return 0;
}
