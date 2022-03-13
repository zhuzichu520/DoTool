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
        bool got = false;
        YUVData data = pItem->getFrame(got);
        if (got)
        {
            m_render.updateTextureData(data);
        }
    }
}

//************VideoItem************//
VideoItem::VideoItem(QQuickItem *parent) : QQuickFramebufferObject (parent)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    startTimer(1);
}

VideoItem::~VideoItem(){

}

void VideoItem::timerEvent(QTimerEvent *event)
{
    update();
}

YUVData VideoItem::getFrame(bool& got)
{
    return m_decoder->getFrame(got);
}

QQuickFramebufferObject::Renderer* VideoItem::createRenderer() const
{
    return new VideoFboItem;
}

void VideoItem::updateVideoSize(int width,int height){
    m_videoWidth = width;
    m_videoHeight = height;
    makeInfoDirty(true);
}

void VideoItem::mousePressEvent(QMouseEvent *event){
    m_decoder->getInputController()->onMouseEvent(event,QSize(videoWidth(),videoHeght()),QSize(width(),height()));
}

void VideoItem::mouseReleaseEvent(QMouseEvent *event){
    m_decoder->getInputController()->onMouseEvent(event,QSize(videoWidth(),videoHeght()),QSize(width(),height()));
}

void VideoItem::mouseMoveEvent(QMouseEvent *event)
{
    m_decoder->getInputController()->onMouseEvent(event,QSize(videoWidth(),videoHeght()),QSize(width(),height()));
}
