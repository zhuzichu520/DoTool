#ifndef SCREENCAPTURECONTROLLER_H
#define SCREENCAPTURECONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QBuffer>
#include <QColor>
#include "GlobalStatic.h"

class ScreenCaptureController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPixmap screenPixmap READ screenPixmap NOTIFY screenPixmapChanged)

    public:
    explicit ScreenCaptureController(QObject *parent = nullptr);
    ~ScreenCaptureController();

    [[nodiscard]] QPixmap screenPixmap() const;
    Q_SIGNAL void screenPixmapChanged();

    Q_INVOKABLE void refreshScreen();
    Q_INVOKABLE void captureRect(int x,int y,int width,int height);
private:
    QPixmap m_screenPixmap;
    QPixmap m_pixmap;
};

#endif // SCREENCAPTURECONTROLLER_H
