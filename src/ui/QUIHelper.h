#ifndef QUIHELPER_H
#define QUIHELPER_H

#include <QObject>
#include <QGuiApplication>
#include <QCursor>
#include <QScreen>
#include <QDebug>
#include <QClipboard>
#include <QCryptographicHash>

class QUIHelper : public QObject
{
    Q_OBJECT
public:
    explicit QUIHelper(QObject *parent = nullptr);
     ~QUIHelper();
    Q_INVOKABLE int getScreenIndex();
    Q_INVOKABLE QRect getScreenRect(bool available);
    Q_INVOKABLE void textClipboard(const QString &text);
    Q_INVOKABLE QString toBase64(const QString&);
    Q_INVOKABLE QString fromBase64(const QString&);
    Q_INVOKABLE QString md5(const QString&);
    Q_INVOKABLE QString sha1(const QString&);
    Q_INVOKABLE QString sha224(const QString&);
    Q_INVOKABLE QString sha256(const QString&);
    Q_INVOKABLE QString sha384(const QString&);
    Q_INVOKABLE QString sha512(const QString&);
signals:

};

#endif // QUIHELPER_H
