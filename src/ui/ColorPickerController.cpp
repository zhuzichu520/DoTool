#include "ColorPickerController.h"

ColorPickerController::ColorPickerController(QObject *parent) : QObject(parent)
{
    qDebug()<<"ColorPickerController()";
}

ColorPickerController::~ColorPickerController()
{
    qDebug()<<"~ColorPickerController()";
}

QString ColorPickerController::screenPixmap() const{
    return m_screenPixmap;
}

void ColorPickerController::refreshScreen(){
    m_pixmap = QGuiApplication::primaryScreen()->grabWindow(0);
    m_screenPixmap = pixmapToString(m_pixmap);
    Q_EMIT screenPixmapChanged();
}

QString ColorPickerController::scalePixmap() const{
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
    m_scalePixmap = pixmapToString(pixmap);
    Q_EMIT scalePixmapChanged();
    Q_EMIT colorTextChanged();
}

QString ColorPickerController::pixmapToString(const QPixmap &pixmap) const{
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer,"JPEG");
    QString image("data:image/jpg;base64,");
    image.append(QString::fromLatin1(bArray.toBase64().data()));
    return image;
}
