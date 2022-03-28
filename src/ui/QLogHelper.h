#ifndef QLOGHELPER_H
#define QLOGHELPER_H

#include <glog/logging.h>
#include <QObject>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>


class QLogHelper : public QObject
{
    Q_OBJECT
public:
    explicit QLogHelper(QObject *parent = nullptr);
    ~QLogHelper();
    void initGoogleLog(char* argv[]);
    std::string toStdString(const QString &str){
        return str.toLocal8Bit().data();
    }
};

#endif // QLOGHELPER_H
