#ifndef PACKCONTROLLER_H
#define PACKCONTROLLER_H

#include <QObject>
#include <QProcess>
#include <QJsonDocument>

class PackController : public QObject
{
    Q_OBJECT
public:
    explicit PackController(QObject *parent = nullptr);
    ~PackController();
    Q_INVOKABLE void pack(const QString& buildDir,const QString& binDir);
private:
    void execute(const QString& cmd);
    QProcess m_process;
};

#endif // PACKCONTROLLER_H
