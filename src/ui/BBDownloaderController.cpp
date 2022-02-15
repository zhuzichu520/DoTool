#include "BBDownloaderController.h"


static constexpr int QrCodeExpireTime = 180; // seconds
static constexpr int PollInterval = 2000; // ms
static constexpr int MaxPollTimes = (QrCodeExpireTime * 1000 / PollInterval) - 3;
static constexpr QColor QrCodeColor = QColor(251, 114, 153); // B站粉

BBDownloaderController::BBDownloaderController(QObject *parent)
    : QObject{parent}
{
    pollTimer = new QTimer(this);
    pollTimer->setInterval(PollInterval);
    pollTimer->setSingleShot(true);
    connect(pollTimer, &QTimer::timeout, this, &BBDownloaderController::pollLoginInfo);
    startGetLoginUrl();
}

QPixmap BBDownloaderController::qrPixmap() const{
    return m_qrPixmap;
}

void BBDownloaderController::startGetLoginUrl(){
    httpReply = Network::Bili::get("https://passport.bilibili.com/qrcode/getLoginUrl");
    connect(httpReply, &QNetworkReply::finished, this, &BBDownloaderController::getLoginUrlFinished);
}

void BBDownloaderController::pollLoginInfo()
{
    auto postData = QString("oauthKey=%1").arg(oauthKey).toUtf8();
    httpReply = Network::Bili::postUrlEncoded("https://passport.bilibili.com/qrcode/getLoginInfo", postData);
    connect(httpReply, &QNetworkReply::finished, this, &BBDownloaderController::getLoginInfoFinished);
}


void BBDownloaderController::getLoginInfoFinished()
{
    polledTimes++;
    auto data = getReplyData();
    if (data.isNull() || data.isUndefined()) {
        // network error
        return;
    }

    bool isPollEnded = false;
    if (data.isDouble()) {
        switch (data.toInt()) {
        case -1: // oauthKey is wrong. should never be this case
            //            QMessageBox::critical(this, "", "oauthKey error");
            break;
        case -2: // login url (qrcode) is expired
            isPollEnded = true;
            qrCodeExpired();
            break;
        case -4: // qrcode not scanned
            break;
        case -5: // scanned but not confirmed
            //            tipLabel->setText("✅扫描成功<br>请在手机上确认");
            break;
        default:
            //            QMessageBox::warning(this, "Poll Warning", QString("unknown code: %1").arg(data.toInteger()));
            break;
        }
    } else {
        // scanned and confirmed
        isPollEnded = true;
        //        accept();
        Q_EMIT loginSuccess();
    }

    if (!isPollEnded) {
        if (polledTimes == MaxPollTimes) {
            Q_EMIT  qrCodeExpired();
        } else {
            pollTimer->start();
        }
    }
}


void BBDownloaderController::refreshExpired(){
    startGetLoginUrl();
}


void BBDownloaderController::getLoginUrlFinished()
{
    auto data = getReplyData().toObject();
    if (data.isEmpty()) {
        // network error
        return;
    }
    QString url = data["url"].toString();
    oauthKey = data["oauthKey"].toString();
    setQrCode(url);
    polledTimes = 0;
    pollTimer->start();
}

QJsonValue BBDownloaderController::getReplyData()
{
    auto reply = httpReply;
    httpReply->deleteLater();
    httpReply = nullptr;
    if (reply->error() == QNetworkReply::OperationCanceledError) {
        return QJsonValue();
    }
    const auto [json, errorString] = Network::Bili::parseReply(reply, "data");
            if (!errorString.isNull()) {
        return QJsonValue();
    }
    return json["data"];
}

void BBDownloaderController::setQrCode(const QString &content)
{
    using namespace qrcodegen;
    QrCode qr = QrCode::encodeText(content.toUtf8(), QrCode::Ecc::MEDIUM);
    int n = qr.getSize();
    QPixmap pixmap(n * 3, n * 3);
    QPainter painter(&pixmap);
    QPen pen(QrCodeColor);
    pen.setWidth(3);
    painter.setPen(pen);
    pixmap.fill();
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            auto val = qr.getModule(col, row);
            if (val) {
                painter.drawPoint(row * 3 + 1, col * 3 + 1);
            }
        }
    }
    m_qrPixmap = pixmap;
    Q_EMIT qrPixmapChanged();
}


