#ifndef UTILS_H
#define UTILS_H

#include<QString>


namespace Utils
{
    // fileExtension("abc.txt") == ".txt"
    // fileExtension("abc") is Null
    QString fileExtension(const QString &fileName);

    int numberOfDigit(int num);

    // pad str(num) with leading 0 so that its length is equal to width
    QString paddedNum(int num, int width);

    // 用全角字符替换视频标题中的 \/:*?"<>| 从而确保文件名合法
    QString legalizedFileName(QString title);

    std::tuple<int, int, int> secs2HMS(int secs);

    QString secs2HmsStr(int secs);

    QString secs2HmsLocaleStr(int secs);

    QString formattedDataSize(qint64 bytes);

} // namespace Utils

#endif // UTILS_H
