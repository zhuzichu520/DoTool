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
        m_mat = cv::imdecode(cv::Mat(data),1);
        setSource(UIHelper->cvMatToQPixmap(m_mat));
        setSize(QSize(maxWidth,m_pixmap.height()*1.0/m_pixmap.width() * maxWidth));
        file.close();
    }
}

void OpencvController::recognizeIdCard(){
    cv::Mat mat = m_mat;
    cv::resize(mat, mat, cv::Size(mat.cols,mat.rows));
    cv::Mat dst;
    cv::cvtColor(mat,dst,cv::COLOR_BGR2GRAY);
    cv::threshold(dst,dst,130,255,cv::THRESH_BINARY);
    cv::erode(dst,dst,cv::getStructuringElement(cv::MORPH_RECT,cv::Size(20,10)));
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Rect> rects;
    cv::findContours(dst, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    LOGI(QString::fromStdString("hahahahahah:%1").arg(contours.size()).toStdString());
    for (int i = 0; i < contours.size(); i++) {
        //获取到矩形区域
        cv::Rect rect = boundingRect(contours.at(i));
        //绘制
        //        rectangle(dst,rect,Scalar(0,0,255));
        //8 逻辑处理，找到号码所在区域
        //身份证号码有固定宽高比>1:8&&<1:16
        if (rect.width > rect.height * 8 && rect.width < rect.height * 16) {
            rects.push_back(rect);
        }
    }
    //9 继续查找坐标最低的矩形区域
    int lowPoint = 0;
    cv::Rect finalRect;
    LOGI(QString::fromStdString("hahahahahah-rects:%1").arg(rects.size()).toStdString());
    for (int i = 0; i < rects.size(); i++) {
        cv::Rect rect = rects.at(i);
        cv::Point point = rect.tl();
        if (point.y > lowPoint) {
            lowPoint = point.y;
            finalRect = rect;
        }
    }
    dst = mat(finalRect);
    setSource(UIHelper->cvMatToQPixmap(dst));
    setSize(QSize(maxWidth,m_pixmap.height()*1.0/m_pixmap.width() * maxWidth));
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
