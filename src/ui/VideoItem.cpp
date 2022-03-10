#include "VideoItem.h"

//************VideoItemRender************//
VideoFboItem::VideoFboItem(){
    m_render.init();
}

void VideoFboItem::render() {
    m_render.paint();
    m_window->resetOpenGLState();
}

QOpenGLFramebufferObject*  VideoFboItem::createFramebufferObject(const QSize &size){
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    m_render.resize(size.width(), size.height());
    return new QOpenGLFramebufferObject(size, format);
}

void VideoFboItem::synchronize(QQuickFramebufferObject *item){
    VideoItem *pItem = qobject_cast<VideoItem *>(item);
    if (pItem)
    {
        if (!m_window)
        {
            m_window = pItem->window();
        }
        if (pItem->infoDirty())
        {
            m_render.updateTextureInfo(pItem->videoWidth(), pItem->videoHeght());
            pItem->makeInfoDirty(false);
        }
        ba = pItem->getFrame();
        m_render.updateTextureData(ba);
    }
}

//************VideoItem************//
VideoItem::VideoItem(QQuickItem *parent) : QQuickFramebufferObject (parent)
{
    startTimer(1);
}

VideoItem::~VideoItem(){

}

void VideoItem::timerEvent(QTimerEvent *event)
{
    update();
}

YUVData VideoItem::getFrame()
{
    return m_decoder->getFrame();
}

QQuickFramebufferObject::Renderer* VideoItem::createRenderer() const
{
    return new VideoFboItem;
}
