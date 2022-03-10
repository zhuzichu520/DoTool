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
    YUVData ba;
};


class VideoItem : public QQuickFramebufferObject
{
    Q_OBJECT
    Q_PROPERTY(PhoneController *decoder READ decoder WRITE setDecoder NOTIFY decoderChanged)
public:
    VideoItem(QQuickItem *parent = nullptr);
    ~VideoItem();
    void timerEvent(QTimerEvent *event) override;

    YUVData getFrame();
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

    PhoneController* decoder(){
        return m_decoder;
    }
    void setDecoder(PhoneController *decoder){
        m_decoder = decoder;
        Q_EMIT decoderChanged();
    }
    Q_SIGNAL void decoderChanged();

public:
    Renderer *createRenderer() const override;
    PhoneController *m_decoder = nullptr;
    int m_videoWidth;
    int m_videoHeight;
    bool m_infoChanged = true;
};

#endif // VIDEOITEM_H
