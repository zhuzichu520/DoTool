#include "ScreenCaptureController.h"

ScreenCaptureController::ScreenCaptureController(QObject *parent) : QObject(parent)
{

}

ScreenCaptureController::~ScreenCaptureController()
{

}

QPixmap ScreenCaptureController::screenPixmap() const{
    return m_screenPixmap;
}

void ScreenCaptureController::refreshScreen(){
    m_pixmap = qApp->screens().at(UIHelper->getScreenIndex())->grabWindow(0);
    m_screenPixmap = m_pixmap;
    Q_EMIT screenPixmapChanged();
}

void ScreenCaptureController::captureRect(int x,int y,int width,int height){
    QPixmap rect = m_pixmap.copy(x,y,width,height);
    qApp->clipboard()->setPixmap(rect);
}
