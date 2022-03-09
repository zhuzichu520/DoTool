#ifndef SCRCPYCONTROLLER_H
#define SCRCPYCONTROLLER_H

#include <QObject>
#include <QDebug>
#include "adbprocess.h"
#include <QPointer>
#include "server.h"
#include "decoder.h"
#include "videobuffer.h"
#include "stream.h"

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
    Q_INVOKABLE void startServer(const QString &);
    Q_INVOKABLE void stopServer();

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
    QPointer<Server> m_server;
    QPointer<Decoder> m_decoder;
    VideoBuffer *m_vb = Q_NULLPTR;
    QStringList m_deviceList;
    QPointer<Stream> m_stream;
};

#endif // SCRCPYCONTROLLER_H
