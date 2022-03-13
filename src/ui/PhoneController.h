#ifndef PHONECONTROLLER_H
#define PHONECONTROLLER_H

#include <QObject>
#include "decoder.h"
#include "stream.h"
#include <QPixmap>
#include "videobuffer.h"
#include <QVideoFrame>
#include <QDebug>
#include "server.h"
#include "controller.h"
#include "bufferutil.h"

const static int bufferSize = 1024*768;

struct YUVData{
    YUVData(){
        Y.reserve(bufferSize);
        U.reserve(bufferSize);
        V.reserve(bufferSize);
    }
    QByteArray Y;
    QByteArray U;
    QByteArray V;
    int yLineSize;
    int uLineSize;
    int vLineSize;
    int height;
};

class PhoneController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPixmap source READ source NOTIFY sourceChanged)
public:
    explicit PhoneController(QObject *parent = nullptr);
    ~PhoneController();

    YUVData getFrame(bool& got){
        if (frameBuffer.isEmpty())
        {
            got = false;
            return {};
        }
        got = true;
        return frameBuffer.takeFirst();
    }

    QPixmap source() const{
        return m_pixmap;
    };


    QPointer<Controller> getInputController(){
        return m_controller;
    }

    Q_SIGNAL void sourceChanged();
    Q_SIGNAL void showPhoneChanged(int width,int height);
    Q_INVOKABLE void startServer(const QString &);
    Q_INVOKABLE void stopServer();

private:
    QPointer<Decoder> m_decoder;
    QPointer<Controller> m_controller;
    VideoBuffer *m_vb = Q_NULLPTR;
    QPointer<Stream> m_stream;
    QPixmap m_pixmap;
    QPointer<Server> m_server;
    YUVData m_yuvData;
    QContiguousCache<YUVData> frameBuffer;
};

#endif // PHONECONTROLLER_H
