#ifndef QUIHELPER_H
#define QUIHELPER_H

#include <QObject>
#include <QGuiApplication>
#include <QCursor>
#include <QScreen>
#include <QDebug>

class QUIHelper : public QObject
{
    Q_OBJECT
public:
    explicit QUIHelper(QObject *parent = nullptr);
     ~QUIHelper();
    Q_INVOKABLE int getScreenIndex();
    Q_INVOKABLE QRect getScreenRect(bool available);
signals:

};

#endif // QUIHELPER_H
