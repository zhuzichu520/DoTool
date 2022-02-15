#ifndef ITEMIMAGE_H
#define ITEMIMAGE_H

#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QPainter>
#include <QImage>
#include <QScreen>


class ItemImage : public QQuickPaintedItem
{
Q_OBJECT
    Q_PROPERTY(QPixmap source READ source WRITE setSource NOTIFY sourceChanged)
public:
    ItemImage(QQuickItem *parent = nullptr);
    Q_INVOKABLE void setSource(const QPixmap &pixmap);
    void paint(QPainter *painter);
    QPixmap source() const;
signals:
    void sourceChanged();
private:
    QPixmap m_pixmap;
};

#endif // ITEMIMAGE_H
