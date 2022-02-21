#include "BBDownloaderController.h"


static constexpr int QrCodeExpireTime = 180; // seconds
static constexpr int PollInterval = 2000; // ms
static constexpr int MaxPollTimes = (QrCodeExpireTime * 1000 / PollInterval) - 3;
static constexpr QColor QrCodeColor = QColor(251, 114, 153); // B站粉
static constexpr int GetUserInfoRetryInterval = 10000; // ms
static constexpr int GetUserInfoTimeout = 10000; // ms


BBDownloaderController::BBDownloaderController(QObject *parent)
    : QObject{parent}
{
    Network::accessManager()->setCookieJar(Settings::inst()->getCookieJar());
    pollTimer = new QTimer(this);
    pollTimer->setInterval(PollInterval);
    pollTimer->setSingleShot(true);
    connect(pollTimer, &QTimer::timeout, this, &BBDownloaderController::pollLoginInfo);
    if(Settings::inst()->hasCookies()){
        setLoginStatus(3);
        startGetUserInfo();
    }else{
        setLoginStatus(0);
        startGetLoginUrl();
    }
}

BBDownloaderController::~BBDownloaderController(){
    if(extractor!=nullptr){
        extractor->deleteLater();
    }
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
            Q_EMIT qrCodeExpired();
            break;
        case -4: // qrcode not scanned
            break;
        case -5: // scanned but not confirmed
            Q_EMIT scanSuccess();
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
        auto settings = Settings::inst();
        settings->saveCookies();
        startGetUserInfo();
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

void BBDownloaderController::startGetUserInfo()
{
    if (!Settings::inst()->hasCookies()) {
        return;
    }
    if (hasGotUInfo || uinfoReply != nullptr) {
        return;
    }
    //    unameLabel->setText("登录中...", Qt::gray);
    auto rqst = Network::Bili::Request(QUrl("https://api.bilibili.com/nav"));
    rqst.setTransferTimeout(GetUserInfoTimeout);
    uinfoReply = Network::accessManager()->get(rqst);;
    connect(uinfoReply, &QNetworkReply::finished, this, &BBDownloaderController::getUserInfoFinished);
}



void BBDownloaderController::getUserInfoFinished()
{
    auto reply = uinfoReply;
    uinfoReply->deleteLater();
    uinfoReply = nullptr;

    if (reply->error() == QNetworkReply::OperationCanceledError) {
        //        unameLabel->setErrText("网络请求超时");
        QTimer::singleShot(GetUserInfoRetryInterval, this, &BBDownloaderController::startGetUserInfo);
        return;
    }

    const auto [json, errorString] = Network::Bili::parseReply(reply, "data");

            if (!json.empty() && !errorString.isNull()) {
        // cookies is wrong, or expired?
        //        unameLabel->clear();
        Settings::inst()->removeCookies();
    } else if (!errorString.isNull()) {
        //        unameLabel->setErrText(errorString);
        QTimer::singleShot(GetUserInfoRetryInterval, this, &BBDownloaderController::startGetUserInfo);
    } else {
        // success
        hasGotUInfo = true;
        auto data = json["data"];
        auto uname = data["uname"].toString();
        ufaceUrl = data["face"].toString() + "@64w_64h.png";
        if (data["vipStatus"].toInt()) {
            setUsername(uname);
            //            unameLabel->setText(uname, B23Style::Pink);
        } else {
            //            unameLabel->setText(uname);
            setUsername(uname);
        }

        //        auto logoutAction = new QAction(QIcon(":/icons/logout.svg"), "退出");
        //        ufaceButton->addAction(logoutAction);
        //        ufaceButton->setIcon(QIcon(":/icons/akkarin.png"));
        //        connect(logoutAction, &QAction::triggered, this, &MainWindow::logoutActionTriggered);

        startGetUFace();
    }
}


QString BBDownloaderController::username() const{
    return m_username;
}

void BBDownloaderController::setUsername(const QString &username){
    m_username = username;
    Q_EMIT usernameChanged();
}

int BBDownloaderController::loginStatus() const{
    return m_loginStatus;
}

void BBDownloaderController::setLoginStatus(int loginStatus){
    m_loginStatus = loginStatus;
    Q_EMIT loginStatusChanged();
}

QPixmap BBDownloaderController::avatar() const{
    return m_avatar;
}

void BBDownloaderController::setAvatar(const QPixmap &pixmap){
    m_avatar = pixmap;
    Q_EMIT avatarChanged();
}

void BBDownloaderController::startGetUFace()
{
    if (ufaceUrl.isNull()) {
        return;
    }
    if (hasGotUFace || uinfoReply != nullptr) {
        return;
    }

    auto rqst = Network::Bili::Request(ufaceUrl);
    rqst.setTransferTimeout(GetUserInfoTimeout);
    uinfoReply = Network::accessManager()->get(rqst);
    connect(uinfoReply, &QNetworkReply::finished, this, &BBDownloaderController::getUFaceFinished);
}

void BBDownloaderController::getUFaceFinished()
{
    auto reply = uinfoReply;
    uinfoReply->deleteLater();
    uinfoReply = nullptr;

    if (!hasGotUInfo && reply->error() == QNetworkReply::OperationCanceledError) {
        // aborted
        return;
    }
    if (reply->error() != QNetworkReply::NoError) {
        QTimer::singleShot(GetUserInfoRetryInterval, this, &BBDownloaderController::startGetUFace);
        return;
    }

    hasGotUFace = true;
    QPixmap pixmap;
    pixmap.loadFromData(reply->readAll());
    setAvatar(pixmap);
    //    ufaceButton->setIcon(QIcon(pixmap));
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

void BBDownloaderController::urlParse(const QString &url){
    if(extractor!=nullptr){
        qDebug()<<"Extractor::deleteLater";
        extractor->deleteLater();
    }
    extractor = new Extractor();
    connect(extractor, &Extractor::success, this,[&]{
        auto result = extractor->getResult();
        setDownTitle(result->title);
        Q_EMIT parseUrlSuccess();
    });
    connect(extractor, &Extractor::errorOccurred, this,&BBDownloaderController::parseUrlError);
    extractor->start(url);
}


