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
    QGuiApplication::setApplicationName("DoTool");
    QGuiApplication::setOrganizationName("DoTool");
    QGuiApplication::setOrganizationDomain("https://github.com/zhuzichu520/DoTool");
    QGuiApplication::setApplicationVersion("1.0");
    QGuiApplication app(argc, argv);
    MainWindow window;
    window.show();
    QGuiApplication::exec();
    return 0;
}
