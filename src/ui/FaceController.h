#ifndef FACECONTROLLER_H
#define FACECONTROLLER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include "GlobalStatic.h"
#include <qmath.h>

class FaceController : public QObject
{
    Q_OBJECT
public:
    explicit FaceController(QObject *parent = nullptr);
    ~FaceController();
private:
};

#endif // OPENCVCONTROLLER_H
