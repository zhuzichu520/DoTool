#ifndef SCRCPYCONTROLLER_H
#define SCRCPYCONTROLLER_H

#include <QObject>
#include <QDebug>
#include "adbprocess.h"

class ScrcpyController : public QObject
{
    Q_OBJECT
public:
    explicit ScrcpyController(QObject *parent = nullptr);
    ~ScrcpyController();
    Q_INVOKABLE void adbExec(const QString &cmd);
signals:
private:
    AdbProcess m_adb;
};

#endif // SCRCPYCONTROLLER_H
