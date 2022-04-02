#include "OpencvController.h"


OpencvController::OpencvController(QObject *parent)
    : QObject{parent}
{

}


void OpencvController::readMat(const QString& path){
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray byteArr = file.readAll();
        std::vector<char> data(byteArr.data(), byteArr.data() +byteArr.size());
        cv::Mat mat = cv::imdecode(cv::Mat(data),1);
        cv::resize(mat, mat, cv::Size(mat.cols,mat.rows));
        cv::Mat dst;
        cv::cvtColor(mat,dst,cv::COLOR_BGR2GRAY);
        cv::threshold(dst,dst,130,255,cv::THRESH_BINARY);
        setSource(UIHelper->cvMatToQPixmap(dst));
        setSize(QSize(maxWidth,m_pixmap.height()*1.0/m_pixmap.width() * maxWidth));
        file.close();
    }
}


QPixmap OpencvController::source() const
{    return this->m_pixmap;
}

void OpencvController::setSource(const QPixmap &pixmap)
{
    this->m_pixmap = pixmap;
    Q_EMIT sourceChanged();
}


void OpencvController::setSize(const QSize &size){
    this->m_size = size;
    Q_EMIT sizeChanged();
}

QSize OpencvController::size() const{
    return this->m_size;
}
