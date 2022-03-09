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
#include "FrameProvider.h"
#include "bufferutil.h"
#include <QPixmap>

class ScrcpyController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList deviceList READ deviceList WRITE setDeviceList NOTIFY deviceListChanged)
    Q_PROPERTY(QPixmap source READ source NOTIFY sourceChanged)
    Q_PROPERTY(FrameProvider* frameProvider READ frameProvider)
public:
    explicit ScrcpyController(QObject *parent = nullptr);
    ~ScrcpyController();
    Q_INVOKABLE void adbExec(const QString &cmd);
    Q_INVOKABLE void oneKeyUsbConnect();
    Q_INVOKABLE void updateDevice();
    Q_INVOKABLE void startServer(const QString &);
    Q_INVOKABLE void stopServer();

    QPixmap source() const{
        return m_pixmap;
    };
    Q_SIGNAL void sourceChanged();

    QStringList deviceList(){
        return m_deviceList;
    }

    FrameProvider* frameProvider(){
        return m_frameProvider;
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
    FrameProvider *m_frameProvider;
    QPointer<Stream> m_stream;
    QPixmap m_pixmap;
};

#endif // SCRCPYCONTROLLER_H
