﻿#include "QUIHelper.h"

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
