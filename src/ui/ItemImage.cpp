// ImageItem.cpp
#include "ItemImage.h"

ItemImage::ItemImage(QQuickItem *parent) : QQuickPaintedItem(parent)
{

}

void ItemImage::paint(QPainter *painter)
{
    painter->drawPixmap(QRect(0,0,width(),height()),m_pixmap);
}

QPixmap ItemImage::source() const
{    return this->m_pixmap;
}

void ItemImage::setSource(const QPixmap &pixmap)
{
    this->m_pixmap = pixmap;
    update();
}
