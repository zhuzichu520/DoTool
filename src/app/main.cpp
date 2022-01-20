#include <QGuiApplication>
#include <QtQuick/qquickwindow.h>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    //    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    //    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QQuickWindow::setSceneGraphBackend(QSGRendererInterface::Software);
    QGuiApplication::setApplicationName("QtTemplate");
    QGuiApplication::setOrganizationName("QtTemplate");
    QGuiApplication::setOrganizationDomain("https://github.com/zhuzichu520/qt-template");
    QGuiApplication::setApplicationVersion("1.0");
    QGuiApplication app(argc, argv);
    MainWindow window;
    window.show();
    QGuiApplication::exec();
    return 0;
}
