#ifndef OPENCVCONTROLLER_H
#define OPENCVCONTROLLER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include "GlobalStatic.h"
#include <qmath.h>

class OpencvController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPixmap source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged)
public:
    explicit OpencvController(QObject *parent = nullptr);
    Q_INVOKABLE void readMat(const QString& path);

    Q_INVOKABLE void setSource(const QPixmap &pixmap);
    QPixmap source() const;
    Q_SIGNAL void sourceChanged();

    Q_INVOKABLE void setSize(const QSize &size);
    QSize size() const;
    Q_SIGNAL void sizeChanged();

    Q_INVOKABLE void recognizeIdCard();
private:
    QPixmap m_pixmap;
    QSize m_size;
    cv::Mat m_mat;
    int maxWidth = 580;
};

#endif // OPENCVCONTROLLER_H
