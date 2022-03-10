#include "VideoItem.h"

//************VideoItemRender************//
class VideoFboItem : public QQuickFramebufferObject::Renderer
{
public:
    VideoFboItem(){
        m_render.init();

        m_render.updateTextureInfo(888, 1920);
    }

    void render() override{
        m_render.paint();
        m_window->resetOpenGLState();
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override{
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setSamples(4);
        m_render.resize(size.width(), size.height());
        return new QOpenGLFramebufferObject(size, format);
    }

    void synchronize(QQuickFramebufferObject *item) override{
        VideoItem *pItem = qobject_cast<VideoItem *>(item);
        if (pItem)
        {
            if (!m_window)
            {
                m_window = pItem->window();
            }
            ba = pItem->getFrame();
            m_render.updateTextureData(ba);
        }
    }
private:
    I420Render m_render;
    QQuickWindow *m_window = nullptr;
    YUVData ba;
};

//************VideoItem************//
VideoItem::VideoItem(QQuickItem *parent) : QQuickFramebufferObject (parent)
{
    startTimer(1);
}

void VideoItem::timerEvent(QTimerEvent *event)
{
    update();
}

YUVData VideoItem::getFrame()
{
    return m_decoder->getFrame();
}

QQuickFramebufferObject::Renderer *VideoItem::createRenderer() const
{
    return new VideoFboItem;
}
