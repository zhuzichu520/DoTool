#include "ColorPickerController.h"

ColorPickerController::ColorPickerController(QObject *parent) : QObject(parent)
{
    qDebug()<<"ColorPickerController()";
}

ColorPickerController::~ColorPickerController()
{
    qDebug()<<"~ColorPickerController()";
}

QPixmap ColorPickerController::screenPixmap() const{
    return m_screenPixmap;
}

void ColorPickerController::refreshScreen(){
    m_pixmap = QGuiApplication::primaryScreen()->grabWindow(0);
    m_screenPixmap = m_pixmap;
    Q_EMIT screenPixmapChanged();
}

QPixmap ColorPickerController::scalePixmap() const{
    return m_scalePixmap;
}

QString ColorPickerController::colorText() const{
    return m_colorText;
}


void ColorPickerController::refreshSclae(int radiusX,int radiusY){
    int radius = 25;
    auto x = radiusX - radius;
    auto y = radiusY - radius;
    auto pixmap = m_pixmap.copy(x,y,2*radius,2*radius);
    m_colorText = QColor(pixmap.toImage().pixel(25,25)).name(QColor::HexRgb);
    m_scalePixmap = pixmap;
    Q_EMIT scalePixmapChanged();
    Q_EMIT colorTextChanged();
}
