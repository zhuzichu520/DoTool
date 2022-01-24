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
    Q_PROPERTY(QString screenPixmap READ screenPixmap NOTIFY screenPixmapChanged)
    Q_PROPERTY(QString scalePixmap READ scalePixmap NOTIFY scalePixmapChanged)
    Q_PROPERTY(QString colorText READ colorText NOTIFY colorTextChanged)

    public:
        explicit ColorPickerController(QObject *parent = nullptr);
    ~ColorPickerController();

    [[nodiscard]] QString screenPixmap() const;
    Q_SIGNAL void screenPixmapChanged();

    [[nodiscard]] QString scalePixmap() const;
    Q_SIGNAL void scalePixmapChanged();

    [[nodiscard]] QString colorText() const;
    Q_SIGNAL void colorTextChanged();

    Q_INVOKABLE void refreshScreen();
    Q_INVOKABLE void refreshSclae(int radiusX,int radiusY);
private:
    [[nodiscard]] QString pixmapToString(const QPixmap &pixmap) const;
private:
    QString m_screenPixmap;
    QString m_scalePixmap;
    QString m_colorText;
    QPixmap m_pixmap;
};

#endif // COLORPICKERCONTROLLER_H
