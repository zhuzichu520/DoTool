#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQmlApplicationEngine>

class Q_DECL_EXPORT MainWindow {
public:
    explicit MainWindow();

    ~MainWindow();

    void show();

protected:
    QQmlApplicationEngine m_engine;
};
#endif
