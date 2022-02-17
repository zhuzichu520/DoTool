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
#include <Settings.h>


class BBDownloaderController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPixmap qrPixmap READ qrPixmap NOTIFY qrPixmapChanged)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QPixmap avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(int loginStatus READ loginStatus WRITE setLoginStatus NOTIFY loginStatusChanged)
public:
    explicit BBDownloaderController(QObject *parent = nullptr);

    [[nodiscard]] QPixmap qrPixmap() const;
    Q_SIGNAL void qrPixmapChanged();

    [[nodiscard]] QString username() const;
    void setUsername(const QString &username);
    Q_SIGNAL void usernameChanged();

    [[nodiscard]] QPixmap avatar() const;
    void setAvatar(const QPixmap &pixmap);
    Q_SIGNAL void avatarChanged();

    [[nodiscard]] int loginStatus() const;
    void setLoginStatus(int loginStatus);
    Q_SIGNAL void loginStatusChanged();

    Q_SIGNAL void qrCodeExpired();
    Q_SIGNAL void loginSuccess();
    Q_SIGNAL void scanSuccess();

    void setQrCode(const QString &content);

    Q_INVOKABLE void refreshExpired();
private:
    QJsonValue getReplyData();
    void startGetLoginUrl();
    void startGetUserInfo();
    void startGetUFace();

private slots:
    void getLoginUrlFinished();
    void pollLoginInfo();
    void getLoginInfoFinished();
    void getUserInfoFinished();
    void getUFaceFinished();
private:
    QPixmap m_qrPixmap;
    QPixmap m_avatar;
    QString m_username;
    QString oauthKey;
    int m_loginStatus;
    int polledTimes = 0;
    QTimer *pollTimer;
    bool hasGotUInfo = false;
    bool hasGotUFace = false;
    QString ufaceUrl;
    QNetworkReply *uinfoReply = nullptr;
    QNetworkReply *httpReply = nullptr;
};

#endif // BBDOWNLOADERCONTROLLER_H
