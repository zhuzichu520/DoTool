#ifndef BBDOWNLOADERCONTROLLER_H
#define BBDOWNLOADERCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QBuffer>
#include <QColor>
#include "Network.h"
#include "QrCode.h"
#include <QtNetwork>
#include <QDataStream>
#include <QPainter>


class BBDownloaderController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPixmap qrPixmap READ qrPixmap NOTIFY qrPixmapChanged)
public:
    explicit BBDownloaderController(QObject *parent = nullptr);

    [[nodiscard]] QPixmap qrPixmap() const;
    Q_SIGNAL void qrPixmapChanged();

    Q_SIGNAL void qrCodeExpired();
    Q_SIGNAL void loginSuccess();
    Q_SIGNAL void scanSuccess();

    void setQrCode(const QString &content);

    Q_INVOKABLE void refreshExpired();
private:
    QJsonValue getReplyData();
    void startGetLoginUrl();
private slots:
    void getLoginUrlFinished();
    void pollLoginInfo();
    void getLoginInfoFinished();
private:
    QPixmap m_qrPixmap;
    QString oauthKey;
    int polledTimes = 0;
    QTimer *pollTimer;
    QNetworkReply *httpReply = nullptr;
};

#endif // BBDOWNLOADERCONTROLLER_H
