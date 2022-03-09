#ifndef BUFFERUTIL_H
#define BUFFERUTIL_H
#include <QBuffer>
#include <QVideoFrame>
#include <QVideoSurfaceFormat>
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavutil/imgutils.h"
}


class BufferUtil
{
public:
    static void write16(QBuffer &buffer, quint32 value);
    static void write32(QBuffer &buffer, quint32 value);
    static void write64(QBuffer &buffer, quint64 value);
    static quint16 read16(QBuffer &buffer);
    static quint32 read32(QBuffer &buffer);
    static quint64 read64(QBuffer &buffer);
    static QVideoFrame avFrameToVideoFrame(const AVFrame *frame);
    static QVideoFrame::PixelFormat ffmpegPixFmtQtFmt(int pix_fmt);
};

#endif // BUFFERUTIL_H
