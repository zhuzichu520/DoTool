#ifndef COLORPICKERCONTROLLER_H
#define COLORPICKERCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QBuffer>
#include <QColor>

class ColorPickerController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPixmap screenPixmap READ screenPixmap NOTIFY screenPixmapChanged)
    Q_PROPERTY(QPixmap scalePixmap READ scalePixmap NOTIFY scalePixmapChanged)
    Q_PROPERTY(QString colorText READ colorText NOTIFY colorTextChanged)

    public:
        explicit ColorPickerController(QObject *parent = nullptr);
    ~ColorPickerController();

    [[nodiscard]] QPixmap screenPixmap() const;
    Q_SIGNAL void screenPixmapChanged();

    [[nodiscard]] QPixmap scalePixmap() const;
    Q_SIGNAL void scalePixmapChanged();

    [[nodiscard]] QString colorText() const;
    Q_SIGNAL void colorTextChanged();

    Q_INVOKABLE void refreshScreen();
    Q_INVOKABLE void refreshSclae(int radiusX,int radiusY);
private:
    QPixmap m_screenPixmap;
    QPixmap m_scalePixmap;
    QString m_colorText;
    QPixmap m_pixmap;
};

#endif // COLORPICKERCONTROLLER_H
