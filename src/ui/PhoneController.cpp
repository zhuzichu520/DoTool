#include "PhoneController.h"

PhoneController::PhoneController(QObject *parent)
    : QObject{parent}
{
    frameBuffer.setCapacity(30);
    m_server = new Server(this);
    m_vb = new VideoBuffer();
    m_vb->init();
    m_decoder = new Decoder(m_vb, this);
    m_stream = new Stream(this);
    if (m_decoder) {
        m_stream->setDecoder(m_decoder);
    }

    if (m_server) {
        connect(m_server, &Server::serverStartResult, this, [this](bool success) {
            if (success) {
                m_server->connectTo();
            } else {

            }
        });
        connect(m_server, &Server::connectToResult, this, [this](bool success, const QString &deviceName, const QSize &size) {
            Q_UNUSED(deviceName);
            if (success) {
                // init decoder
                m_stream->setVideoSocket(m_server->getVideoSocket());
                m_stream->startDecode();
                Q_EMIT showPhoneChanged(size.width(),size.height());
            }
        });
        connect(m_server, &Server::onServerStop, this, [this]() {
            deleteLater();
            qDebug() << "server process stop";
        });
    }


    if (m_decoder && m_vb) {
        // must be Qt::QueuedConnection, ui update must be main thread
        connect(
                    m_decoder,
                    &Decoder::onNewFrame,
                    this,
                    [this]() {
            m_vb->lock();
            const AVFrame *yuvFrame = m_vb->consumeRenderedFrame();
            qDebug()<<yuvFrame->width;
            qDebug()<<yuvFrame->height;
            //            QVideoFrame f = BufferUtil::avFrameToVideoFrame(frame);
            //                m_pixmap = QPixmap::fromImage(f.image());
            //            Q_EMIT sourceChanged();
            m_yuvData.Y.resize(yuvFrame->linesize[0]*yuvFrame->height);
            m_yuvData.Y =QByteArray((char*)yuvFrame->data[0],m_yuvData.Y.size());
            m_yuvData.U.resize(yuvFrame->linesize[1]*yuvFrame->height/2);
            m_yuvData.U =QByteArray((char*)yuvFrame->data[1],m_yuvData.U.size());
            m_yuvData.V.resize(yuvFrame->linesize[2]*yuvFrame->height/2);
            m_yuvData.V =QByteArray((char*)yuvFrame->data[2],m_yuvData.V.size());
            m_yuvData.yLineSize = yuvFrame->linesize[0];
            m_yuvData.uLineSize = yuvFrame->linesize[1];
            m_yuvData.vLineSize = yuvFrame->linesize[2];
            m_yuvData.height = yuvFrame->height;
            frameBuffer.append(m_yuvData);
            m_vb->unLock();
        },
        Qt::QueuedConnection);
    }
}

PhoneController::~PhoneController(){
    if (m_server) {
        m_server->stop();
    }
    // server must stop before decoder, because decoder block main thread
    if (m_stream) {
        m_stream->stopDecode();
    }
    if (m_vb) {
        m_vb->deInit();
        delete m_vb;
    }
}

void PhoneController::startServer(const QString &serial){
    Server::ServerParams params;
    params.serial = serial;
    params.maxSize = 1920;
    m_server->start(params);
}

void PhoneController::stopServer(){
    if (m_server) {
        m_server->stop();
    }
}
