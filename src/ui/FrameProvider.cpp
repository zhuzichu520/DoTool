#include "FrameProvider.h"


FrameProvider::FrameProvider(QObject *parent)
    : QObject{parent}
{

}

FrameProvider::~FrameProvider()
{
}


void FrameProvider::onNewVideoContentReceived(const QVideoFrame &frame)
{
    if (m_surface)
        m_surface->present(frame);
}

void FrameProvider::setFormat(int width, int heigth, QVideoFrame::PixelFormat format)
{
    QSize size(width, heigth);
    QVideoSurfaceFormat surformat(size, format);
    m_format = surformat;
    if (m_surface)
    {
        if (m_surface->isActive())
        {
            m_surface->stop();
        }
        m_format = m_surface->nearestFormat(m_format);
        m_surface->start(m_format);
    }
}


void FrameProvider::setVideoSurface(QAbstractVideoSurface *surface)
   {
       if (m_surface && m_surface != surface  && m_surface->isActive()) {
           m_surface->stop();
       }
       m_surface = surface;
       if (m_surface && m_format.isValid())
       {
           m_format = m_surface->nearestFormat(m_format);
           m_surface->start(m_format);

       }
   }
