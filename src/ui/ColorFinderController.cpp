#include "ColorFinderController.h"

ColorFinderController::ColorFinderController(QObject *parent) : QObject(parent)
{
    qDebug()<<"ColorFinderController()";
}

ColorFinderController::~ColorFinderController()
{
    qDebug()<<"~ColorFinderController()";
}

QPixmap ColorFinderController::screenPixmap() const{
    return m_screenPixmap;
}

void ColorFinderController::refreshScreen(){
    m_pixmap = qApp->screens().at(UIHelper->getScreenIndex())->grabWindow(0);
    m_screenPixmap = m_pixmap;
    Q_EMIT screenPixmapChanged();
}

QPixmap ColorFinderController::scalePixmap() const{
    return m_scalePixmap;
}

QString ColorFinderController::colorText() const{
    return m_colorText;
}


void ColorFinderController::refreshSclae(int radiusX, int radiusY){
    int radius = 25;
    auto x = radiusX - radius;
    auto y = radiusY - radius;
    auto pixmap = m_pixmap.copy(x,y,2*radius,2*radius);
    m_colorText = QColor(pixmap.toImage().pixel(25,25)).name(QColor::HexRgb);
    m_scalePixmap = pixmap;
    Q_EMIT scalePixmapChanged();
    Q_EMIT colorTextChanged();
}
