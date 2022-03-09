#ifndef ITEMIMAGE_H
#define ITEMIMAGE_H

#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QPainter>
#include <QImage>
#include <QScreen>
#include <QPainterPath>

class ItemImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QPixmap source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(bool round READ round WRITE setRound NOTIFY roundChanged)
public:
    ItemImage(QQuickItem *parent = nullptr);
    void paint(QPainter *painter);

    Q_INVOKABLE void setSource(const QPixmap &pixmap);
    QPixmap source() const;
    Q_SIGNAL void sourceChanged();

    [[nodiscard]] bool round() const;
    void setRound(bool round);
    Q_SIGNAL void roundChanged();


private:
    QPixmap m_pixmap;
    int m_round;
};

#endif // ITEMIMAGE_H
