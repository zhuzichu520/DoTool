#ifndef VIDEOITEM_H
#define VIDEOITEM_H

#include <QObject>
#include <memory>
#include <QQuickItem>
#include <QQuickFramebufferObject>
#include <QTimerEvent>
#include <QQuickWindow>
#include "PhoneController.h"
#include "I420Render.h"
#include <QOpenGLFramebufferObjectFormat>


class VideoFboItem : public QQuickFramebufferObject::Renderer
{
public:
    VideoFboItem();

    void render() override;

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

    void synchronize(QQuickFramebufferObject *item) override;

    I420Render m_render;
private:
    QQuickWindow *m_window = nullptr;
};


class VideoItem : public QQuickFramebufferObject
{
    Q_OBJECT
    Q_PROPERTY(PhoneController *decoder READ decoder WRITE setDecoder NOTIFY decoderChanged)
public:
    VideoItem(QQuickItem *parent = nullptr);
    ~VideoItem();
    void timerEvent(QTimerEvent *event) override;

    YUVData getFrame(bool& got);
    bool infoDirty() const
    {
        return m_infoChanged;
    }
    void makeInfoDirty(bool dirty)
    {
        m_infoChanged = dirty;
    }
    int videoWidth() const
    {
        return m_videoWidth;
    }
    int videoHeght() const
    {
        return m_videoHeight;
    }

    int videoFormat() const
    {
        return m_videoFormat;
    }

    PhoneController* decoder(){
        return m_decoder;
    }
    void setDecoder(PhoneController *decoder){
        m_decoder = decoder;
        Q_EMIT decoderChanged();
    }

    Q_INVOKABLE void updateVideoSize(int width,int height);

    Q_SIGNAL void decoderChanged();


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public:
    Renderer *createRenderer() const override;
    PhoneController *m_decoder = nullptr;
    int m_videoWidth;
    int m_videoHeight;
    int m_videoFormat;
    bool m_infoChanged = false;
};

#endif // VIDEOITEM_H
