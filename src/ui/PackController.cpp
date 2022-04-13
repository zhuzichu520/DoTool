#include "PackController.h"
#include "GlobalStatic.h"
#include <QStringList>

PackController::PackController(QObject *parent)
    : QObject{parent}
{
    LOGI("pwd");

    connect(&m_process,&QProcess::readyReadStandardOutput,this,[&](){
        LOGI("--------------------------");
        QString temp =  m_process.readAll();
        LOGI(temp.toStdString());
    });

    connect(&m_process,&QProcess::readyReadStandardError,this,[&](){
        LOGI("------------readyReadStandardError--------------");
    });

}

PackController::~PackController(){

}

void PackController::pack(const QString& buildDir,const QString& binDir){
    execute(buildDir+"\\bin\\windeployqt.exe "+binDir);
}

void PackController::execute(const QString& cmd){
       m_process.start("cmd",QStringList()<<"/c"<<cmd,QIODevice::ReadWrite);
}
