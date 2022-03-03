#include <QGuiApplication>
#include <QtQuick/qquickwindow.h>
#include "MainWindow.h"
#include <QFont>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
//        QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
//        QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);
    QQuickWindow::setSceneGraphBackend(QSGRendererInterface::Software);
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
