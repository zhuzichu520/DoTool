#include "QUIHelper.h"

QUIHelper::QUIHelper(QObject *parent)
    : QObject{parent}
{

}

QUIHelper::~QUIHelper()
{

}

void QUIHelper::setCode()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif
}

//获取当前屏幕索引
int QUIHelper::getScreenIndex()
{
    //需要对多个屏幕进行处理
    int screenIndex = 0;
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    int screenCount = qApp->screens().count();
#else
    int screenCount = qApp->desktop()->screenCount();
#endif

    if (screenCount > 1) {
        //找到当前鼠标所在屏幕
        QPoint pos = QCursor::pos();
        for (int i = 0; i < screenCount; ++i) {
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
            if (qApp->screens().at(i)->geometry().contains(pos)) {
#else
            if (qApp->desktop()->screenGeometry(i).contains(pos)) {
#endif
                screenIndex = i;
                break;
            }
        }
    }
    return screenIndex;
}

//获取当前屏幕尺寸区域
QRect QUIHelper::getScreenRect(bool available)
{
    QRect rect;
    int screenIndex = QUIHelper::getScreenIndex();
    if (available) {
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
        rect = qApp->screens().at(screenIndex)->availableGeometry();
#else
        rect = qApp->desktop()->availableGeometry(screenIndex);
#endif
    } else {
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
        rect = qApp->screens().at(screenIndex)->geometry();
#else
        rect = qApp->desktop()->screenGeometry(screenIndex);
#endif
    }
    return rect;
}

void QUIHelper::textClipboard(const QString &text){
    qApp->clipboard()->setText(text);
}

QString QUIHelper::toBase64(const QString &text){
    return text.toUtf8().toBase64();
}

QString QUIHelper::fromBase64(const QString &text){
    return QByteArray::fromBase64(text.toUtf8());
}

QString QUIHelper::md5(const QString &text){
    return QCryptographicHash::hash(text.toUtf8(),QCryptographicHash::Md5).toHex();
}

QString QUIHelper::sha1(const QString &text){
    return QCryptographicHash::hash(text.toUtf8(),QCryptographicHash::Sha1).toHex();
}

QString QUIHelper::sha224(const QString &text){
    return QCryptographicHash::hash(text.toUtf8(),QCryptographicHash::Sha224).toHex();
}

QString QUIHelper::sha256(const QString &text){
    return QCryptographicHash::hash(text.toUtf8(),QCryptographicHash::Sha256).toHex();
}

QString QUIHelper::sha384(const QString &text){
    return QCryptographicHash::hash(text.toUtf8(),QCryptographicHash::Sha384).toHex();
}

QString QUIHelper::sha512(const QString &text){
    return QCryptographicHash::hash(text.toUtf8(),QCryptographicHash::Sha512).toHex();
}

QImage QUIHelper:: cvMatToQImage( const cv::Mat &inMat )
{
    switch ( inMat.type() )
    {
    case CV_8UC4:
    {
        QImage image(inMat.data,inMat.cols, inMat.rows,static_cast<int>(inMat.step),QImage::Format_ARGB32 );
        return image;
    }
    case CV_8UC3:
    {
        QImage image(inMat.data,inMat.cols, inMat.rows,static_cast<int>(inMat.step),QImage::Format_RGB888 );
        return image.rgbSwapped();
    }
    case CV_8UC1:
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image(inMat.data,inMat.cols, inMat.rows,static_cast<int>(inMat.step),QImage::Format_Grayscale8 );
#else
        static QVector<QRgb>  sColorTable;
        if (sColorTable.isEmpty())
        {
            sColorTable.resize(256);
            for ( int i = 0; i < 256; ++i )
            {
                sColorTable[i] = qRgb( i, i, i );
            }
        }
        QImage image(inMat.data,inMat.cols, inMat.rows,static_cast<int>(inMat.step),QImage::Format_Indexed8 );
        image.setColorTable( sColorTable );
#endif
        return image;
    }
    default:
        qWarning() << "CVS::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }
    return QImage();
}

QPixmap QUIHelper:: cvMatToQPixmap( const cv::Mat &inMat )
{
    return QPixmap::fromImage( cvMatToQImage( inMat ) );
}

cv::Mat QUIHelper:: QImageToCvMat( const QImage &inImage, bool inCloneImageData)
{
    switch ( inImage.format() )
    {
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
    {
        cv::Mat  mat(inImage.height(), inImage.width(),CV_8UC4,const_cast<uchar*>(inImage.bits()), static_cast<size_t>(inImage.bytesPerLine()));
        return (inCloneImageData ? mat.clone() : mat);
    }
    case QImage::Format_RGB32:
    case QImage::Format_RGB888:
    {
        if ( !inCloneImageData )
        {
            qWarning() << "CVS::QImageToCvMat() - Conversion requires cloning because we use a temporary QImage";
        }
        QImage   swapped = inImage;
        if ( inImage.format() == QImage::Format_RGB32 )
        {
            swapped = swapped.convertToFormat( QImage::Format_RGB888 );
        }
        swapped = swapped.rgbSwapped();
        return cv::Mat(swapped.height(), swapped.width(),CV_8UC3,const_cast<uchar*>(swapped.bits()),static_cast<size_t>(swapped.bytesPerLine())).clone();
    }
    case QImage::Format_Indexed8:
    {
        cv::Mat  mat(inImage.height(), inImage.width(),CV_8UC1,const_cast<uchar*>(inImage.bits()),static_cast<size_t>(inImage.bytesPerLine()));
        return (inCloneImageData ? mat.clone() : mat);
    }
    default:
        qWarning() << "CVS::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
        break;
    }
    return cv::Mat();
}

cv::Mat QUIHelper::QPixmapToCvMat( const QPixmap &inPixmap, bool inCloneImageData)
{
    return QImageToCvMat( inPixmap.toImage(), inCloneImageData );
}

QString QUIHelper::readFile(const QString &fileName)
{
    QString content;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        content = stream.readAll();
    }
    return content;
}


void QUIHelper::checkUpdate(){
    QString program("./maintenancetool.exe");
    QStringList checkArgs;
    checkArgs << "--checkupdates";
    // 检测更新
    QProcess process;
    process.start(program, checkArgs);
    // 等待检测完成
    if (!process.waitForFinished()) {
        LOG(INFO)<<"Error checking for updates.";
        Q_EMIT checkUpdateResult(-1);
        return;
    }
    QString data = process.readAllStandardOutput();
    if (data.isEmpty()) {
        LOG(INFO)<<"No updates available.";
        Q_EMIT checkUpdateResult(0);
        return;
    }

    if(data.contains("no updates available")){
        LOG(INFO)<<"No updates available.";
        Q_EMIT checkUpdateResult(0);
        return;
    }

    if(data.contains("Warning:")){
        LOG(INFO)<<"No updates available.";
        Q_EMIT checkUpdateResult(-1);
        return;
    }

    QStringList updaterArgs;
    updaterArgs << "--updater";
    bool success = QProcess::startDetached(program, updaterArgs);
    if (!success) {
        qDebug() << "Program startup failed.";
        return;
    }

    LOG(INFO)<<data.toStdString();
    Q_EMIT checkUpdateResult(1);
}
