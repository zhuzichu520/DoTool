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

class VideoItem : public QQuickFramebufferObject
{
    Q_OBJECT
    Q_PROPERTY(PhoneController *decoder READ decoder WRITE setDecoder NOTIFY decoderChanged)
public:
    VideoItem(QQuickItem *parent = nullptr);
    void timerEvent(QTimerEvent *event) override;

    YUVData getFrame();

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
};

#endif // VIDEOITEM_H
