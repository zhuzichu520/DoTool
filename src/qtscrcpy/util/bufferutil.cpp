#include "bufferutil.h"

void BufferUtil::write32(QBuffer &buffer, quint32 value)
{
    buffer.putChar(value >> 24);
    buffer.putChar(value >> 16);
    buffer.putChar(value >> 8);
    buffer.putChar(value);
}

void BufferUtil::write64(QBuffer &buffer, quint64 value)
{
    write32(buffer, value >> 32);
    write32(buffer, (quint32)value);
}

void BufferUtil::write16(QBuffer &buffer, quint32 value)
{
    buffer.putChar(value >> 8);
    buffer.putChar(value);
}

quint16 BufferUtil::read16(QBuffer &buffer)
{
    uchar c;
    quint16 ret = 0;
    buffer.getChar(reinterpret_cast<char *>(&c));
    ret |= (c << 8);
    buffer.getChar(reinterpret_cast<char *>(&c));
    ret |= c;

    return ret;
}

quint32 BufferUtil::read32(QBuffer &buffer)
{
    uchar c;
    quint32 ret = 0;
    buffer.getChar(reinterpret_cast<char *>(&c));
    ret |= (c << 24);
    buffer.getChar(reinterpret_cast<char *>(&c));
    ret |= (c << 16);
    buffer.getChar(reinterpret_cast<char *>(&c));
    ret |= (c << 8);
    buffer.getChar(reinterpret_cast<char *>(&c));
    ret |= c;

    return ret;
}

quint64 BufferUtil::read64(QBuffer &buffer)
{
    quint32 msb = read32(buffer);
    quint32 lsb = read32(buffer);

    return ((quint64)msb << 32) | lsb;
    ;
}

QVideoFrame BufferUtil::avFrameToVideoFrame(const AVFrame *frame){
    QVideoSurfaceFormat format = QVideoSurfaceFormat(QSize(frame->width, frame->height), ffmpegPixFmtQtFmt(frame->format));
    int imagesize = av_image_get_buffer_size((AVPixelFormat)frame->format,frame->width,frame->height,1);
    QVideoFrame f(imagesize,QSize(frame->width,frame->height),frame->width,format.pixelFormat());
    if (f.map(QAbstractVideoBuffer::WriteOnly))
        {
            uchar * fdata = f.bits();
            av_image_copy_to_buffer(fdata, imagesize, frame->data, frame->linesize, (AVPixelFormat)frame->format, frame->width, frame->height, 1);
            f.unmap();
            f.setStartTime(0);
            return f;
        }
    return f;
}

QVideoFrame::PixelFormat BufferUtil::ffmpegPixFmtQtFmt(int pix_fmt){
    switch (pix_fmt)
    {
    case AV_PIX_FMT_YUV420P:
    case AV_PIX_FMT_YUVJ420P:
    {
        return QVideoFrame::Format_YUV420P;
    }
    case AV_PIX_FMT_NV12:
    {
        return QVideoFrame::Format_NV12;
    }
    default:
        return QVideoFrame::Format_Invalid;
    }
}
