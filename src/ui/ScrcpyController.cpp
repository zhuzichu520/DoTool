#include "ScrcpyController.h"

ScrcpyController::ScrcpyController(QObject *parent)
    : QObject{parent}
{
    connect(&m_adb, &AdbProcess::adbProcessResult, this, [this](AdbProcess::ADB_EXEC_RESULT processResult) {
        QString log = "";
        bool newLine = true;
        QStringList args = m_adb.arguments();

        switch (processResult) {
        case AdbProcess::AER_ERROR_START:
            break;
        case AdbProcess::AER_SUCCESS_START:
            log = "adb run";
            newLine = false;
            break;
        case AdbProcess::AER_ERROR_EXEC:
            log = m_adb.getErrorOut();
            if (args.contains("ifconfig") && args.contains("wlan0")) {
                //                getIPbyIp();
            }
            break;
        case AdbProcess::AER_ERROR_MISSING_BINARY:
            log = "adb not found";
            break;
        case AdbProcess::AER_SUCCESS_EXEC:
            log = m_adb.getStdOut();
            if (args.contains("devices")) {
                QStringList devices = m_adb.getDevicesSerialFromStdOut();
                setDeviceList(devices);
            } else if (args.contains("show") && args.contains("wlan0")) {
                QString ip = m_adb.getDeviceIPFromStdOut();
                if (ip.isEmpty()) {
                    log = "ip not find, connect to wifi?";
                    break;
                }
                //                ui->deviceIpEdt->setText(ip);
            } else if (args.contains("ifconfig") && args.contains("wlan0")) {
                QString ip = m_adb.getDeviceIPFromStdOut();
                if (ip.isEmpty()) {
                    log = "ip not find, connect to wifi?";
                    break;
                }
                //                ui->deviceIpEdt->setText(ip);
            } else if (args.contains("ip -o a")) {
                QString ip = m_adb.getDeviceIPByIpFromStdOut();
                if (ip.isEmpty()) {
                    log = "ip not find, connect to wifi?";
                    break;
                }
                //                ui->deviceIpEdt->setText(ip);
            }
            break;
        }
        if (!log.isEmpty()) {
            Q_EMIT outLog(log, newLine);
        }
    });


}

ScrcpyController::~ScrcpyController(){

}


void ScrcpyController::oneKeyUsbConnect(){
    updateDevice();
}

void ScrcpyController::updateDevice(){
    Q_EMIT outLog("update devices...", false);
    m_adb.execute("", QStringList() << "devices");
}

void ScrcpyController::adbExec(const QString &cmd){
    qDebug()<<".................."+cmd;
    m_adb.execute(cmd,cmd.split(" ", Qt::SkipEmptyParts));
}
