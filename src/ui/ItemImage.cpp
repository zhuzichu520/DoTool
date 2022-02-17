// ImageItem.cpp
#include "ItemImage.h"

ItemImage::ItemImage(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    setRound(false);
}

void ItemImage::paint(QPainter *painter)
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing, true);
    if(m_round){
        QPainterPath path;
        path.addEllipse(0, 0, width(), height());
        painter->setClipPath(path);
    }
    painter->drawPixmap(QRect(0, 0, static_cast<int>(width()), static_cast<int>(height())), m_pixmap);
    painter->restore();
}

QPixmap ItemImage::source() const
{    return this->m_pixmap;
}

void ItemImage::setSource(const QPixmap &pixmap)
{
    this->m_pixmap = pixmap;
    update();
    Q_EMIT sourceChanged();
}

bool ItemImage::round() const{
    return m_round;
}

void ItemImage::setRound(bool round){
    m_round = round;
    update();
    Q_EMIT roundChanged();
}
