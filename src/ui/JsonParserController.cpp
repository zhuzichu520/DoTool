#include "JsonParserController.h"


JsonParserController::JsonParserController(QObject *parent)
    : QObject{parent}
{

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
