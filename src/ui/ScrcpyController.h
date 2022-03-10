#ifndef SCRCPYCONTROLLER_H
#define SCRCPYCONTROLLER_H

#include <QObject>
#include <QDebug>
#include "adbprocess.h"
#include <QPointer>

class ScrcpyController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList deviceList READ deviceList WRITE setDeviceList NOTIFY deviceListChanged)

public:
    explicit ScrcpyController(QObject *parent = nullptr);
    ~ScrcpyController();
    Q_INVOKABLE void adbExec(const QString &cmd);
    Q_INVOKABLE void oneKeyUsbConnect();
    Q_INVOKABLE void updateDevice();

    QStringList deviceList(){
        return m_deviceList;
    }

    void setDeviceList(const QStringList &data){
        m_deviceList = data;
        Q_EMIT deviceListChanged();
    }

    Q_SIGNAL void deviceListChanged();

signals:
    void outLog(const QString &log, bool newLine);
private:
    AdbProcess m_adb;
    QStringList m_deviceList;
};

#endif // SCRCPYCONTROLLER_H
