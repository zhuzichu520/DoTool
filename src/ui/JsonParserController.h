#ifndef JSONPARSERCONTROLLER_H
#define JSONPARSERCONTROLLER_H

#include <QObject>
#include <QJsonDocument>

class JsonParserController : public QObject
{
    Q_OBJECT
public:
    explicit JsonParserController(QObject *parent = nullptr);

    Q_INVOKABLE QString jsonFormat(const QString &json);
signals:

};

#endif // JSONPARSERCONTROLLER_H
