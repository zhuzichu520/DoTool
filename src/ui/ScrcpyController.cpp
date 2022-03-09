#include "ScrcpyController.h"

ScrcpyController::ScrcpyController(QObject *parent)
    : QObject{parent}
{
    m_frameProvider =new FrameProvider;
    m_vb = new VideoBuffer();
    m_vb->init();
    m_decoder = new Decoder(m_vb, this);
    m_stream = new Stream(this);
    if (m_decoder) {
        m_stream->setDecoder(m_decoder);
    }
    m_server = new Server(this);
    connect(&m_adb, &AdbProcess::adbProcessResult, this, [this](AdbProcess::ADB_EXEC_RESULT processResult) {
        QString log = "";
        bool newLine = true;
        QStringList args = m_adb.arguments();

        switch (processResult) {
        case AdbProcess::AER_ERROR_START:
            break;
        case AdbProcess::AER_SUCCESS_START:
            log = "adb run";
            newLine = false;
            break;
        case AdbProcess::AER_ERROR_EXEC:
            log = m_adb.getErrorOut();
            if (args.contains("ifconfig") && args.contains("wlan0")) {
                //                getIPbyIp();
            }
            break;
        case AdbProcess::AER_ERROR_MISSING_BINARY:
            log = "adb not found";
            break;
        case AdbProcess::AER_SUCCESS_EXEC:
            log = m_adb.getStdOut();
            if (args.contains("devices")) {
                QStringList devices = m_adb.getDevicesSerialFromStdOut();
                setDeviceList(devices);
                //                ui->serialBox->clear();
                //                ui->connectedPhoneList->clear();
                //                for (auto &item : devices) {
                //                   Q_EMIT outLog(item,false);
                //                    ui->serialBox->addItem(item);
                //                    ui->connectedPhoneList->addItem(Config::getInstance().getNickName(item) + "-" + item);
                //                }
            } else if (args.contains("show") && args.contains("wlan0")) {
                QString ip = m_adb.getDeviceIPFromStdOut();
                if (ip.isEmpty()) {
                    log = "ip not find, connect to wifi?";
                    break;
                }
                //                ui->deviceIpEdt->setText(ip);
            } else if (args.contains("ifconfig") && args.contains("wlan0")) {
                QString ip = m_adb.getDeviceIPFromStdOut();
                if (ip.isEmpty()) {
                    log = "ip not find, connect to wifi?";
                    break;
                }
                //                ui->deviceIpEdt->setText(ip);
            } else if (args.contains("ip -o a")) {
                QString ip = m_adb.getDeviceIPByIpFromStdOut();
                if (ip.isEmpty()) {
                    log = "ip not find, connect to wifi?";
                    break;
                }
                //                ui->deviceIpEdt->setText(ip);
            }
            break;
        }
        if (!log.isEmpty()) {
            Q_EMIT outLog(log, newLine);
        }
    });

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
                const AVFrame *frame = m_vb->consumeRenderedFrame();
                qDebug()<<frame->width;
                qDebug()<<frame->height;
                QVideoFrame f = BufferUtil::avFrameToVideoFrame(frame);
                m_pixmap = QPixmap::fromImage(f.image());
                Q_EMIT sourceChanged();
                m_vb->unLock();
            },
            Qt::QueuedConnection);
    }

}

ScrcpyController::~ScrcpyController(){
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
    if(m_frameProvider){
        m_frameProvider->deleteLater();
    }
}

void ScrcpyController::startServer(const QString &serial){
    Server::ServerParams params;
    params.serial = serial;
    m_server->start(params);
}

void ScrcpyController::stopServer(){
    if (m_server) {
        m_server->stop();
    }
    if (m_stream) {
        m_stream->stopDecode();
    }
    if (m_vb) {
        m_vb->deInit();
    }
}

void ScrcpyController::oneKeyUsbConnect(){
    Server::ServerParams params;
    updateDevice();
}

void ScrcpyController::updateDevice(){
    m_adb.execute("", QStringList() << "devices");
}

void ScrcpyController::adbExec(const QString &cmd){
    qDebug()<<".................."+cmd;
    m_adb.execute(cmd,cmd.split(" ", Qt::SkipEmptyParts));
}
