#include "ScreenImageProvider.h"

QPixmap ScreenImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize){
    qDebug()<<"requestPixmap-id:"<<id;
    if(id=="refresh"){
        m_screen = QGuiApplication::primaryScreen();
    }

    return m_screen->grabWindow(0);
}
