#include "JsonParserController.h"
#include "GlobalStatic.h"

JsonParserController::JsonParserController(QObject *parent)
    : QObject{parent}
{
    LOGI("执行了");
}

JsonParserController::~JsonParserController(){

}

QString JsonParserController::jsonFormat(const QString &json){
    QJsonParseError *error=new QJsonParseError;
    QJsonDocument jdc = QJsonDocument::fromJson(json.toUtf8(),error);
    if(error->error!=QJsonParseError::NoError){
        return error->errorString();
    }
    return jdc.toJson(QJsonDocument::Indented);
}
