#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQmlApplicationEngine>

class MainWindow {
public:
    explicit MainWindow();

    ~MainWindow();

    void show();

protected:
    QQmlApplicationEngine m_engine;
};
#endif
