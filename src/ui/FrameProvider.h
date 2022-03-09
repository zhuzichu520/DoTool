#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include <QObject>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>

class FrameProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)
public:
    explicit FrameProvider(QObject *parent = nullptr);
    ~FrameProvider();
    QAbstractVideoSurface* videoSurface() const;
    void setVideoSurface(QAbstractVideoSurface *surface);
    void setFormat(int width, int heigth, QVideoFrame::PixelFormat format);
public slots:
    void onNewVideoContentReceived(const QVideoFrame &frame);
private:
    QAbstractVideoSurface *m_surface = NULL;
    QVideoSurfaceFormat m_format;

};

#endif // FRAMEPROVIDER_H
