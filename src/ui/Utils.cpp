// Created by voidzero <vooidzero.github@qq.com>

#include "Utils.h"
#include <QPainter>
#include <QHelpEvent>


QString Utils::fileExtension(const QString &fileName)
{
    auto dotPos = fileName.lastIndexOf('.');
    if (dotPos < 0) {
        return QString();
    }
    return fileName.mid(dotPos+1);
}

int Utils::numberOfDigit(int num)
{
    if (num == 0) {
        return 1;
    }
    int ret = 0;
    while (num != 0) {
        num /= 10;
        ret++;
    }
    return ret;
}

QString Utils::paddedNum(int num, int width)
{
    auto s = QString::number(num);
    auto padWidth = width - s.size();
    s.prepend(QString(padWidth, '0'));
    return s;
}

QString Utils::legalizedFileName(QString title)
{
    return title.simplified()
            .replace('\\', u'＼').replace('/', u'／').replace(':', u'：')
            .replace('*', u'＊').replace('?', u'？').replace('"', u'“')
            .replace('<', u'＜').replace('>', u'＞').replace('|', u'｜');
    // 整个路径的合法性检查可以参考 https://stackoverflow.com/q/62771
}

std::tuple<int, int, int> Utils::secs2HMS(int secs)
{
    auto s = secs % 60;
    auto mins = secs / 60;
    auto m = mins % 60;
    auto h = mins / 60;
    return { h, m, s };
}


QString Utils::secs2HmsStr(int secs)
{
    auto [h, m, s] = secs2HMS(secs);
    QLatin1Char fillChar('0');
    return QStringLiteral("%1:%2:%3")
            .arg(h, 2, 10, fillChar)
            .arg(m, 2, 10, fillChar)
            .arg(s, 2, 10, fillChar);
}

QString Utils::secs2HmsLocaleStr(int secs)
{
    auto [h, m, s] = secs2HMS(secs);
    QString ret;
    int fieldWidth = 1;
    QLatin1Char fillChar('0');
    if (h != 0) {
        ret.append(QString::number(h) + "小时");
        fieldWidth = 2;
    }
    if (m != 0) {
        ret.append(QStringLiteral("%1分").arg(m, fieldWidth, 10, fillChar));
        fieldWidth = 2;
    }
    ret.append(QStringLiteral("%1秒").arg(s, fieldWidth, 10, fillChar));
    return ret;
}

QString Utils::formattedDataSize(qint64 bytes)
{
    constexpr qint64 Kilo = 1024;
    constexpr qint64 Mega = 1024 * 1024;
    constexpr qint64 Giga = 1024 * 1024 * 1024;

    if (bytes > Giga) {
        return QString::number(static_cast<double>(bytes) / Giga, 'f', 2) + " GB";
    } else if (bytes > Mega) {
        return QString::number(static_cast<double>(bytes) / Mega, 'f', 2) + " MB";
    } else if (bytes > Kilo) {
        return QString::number(static_cast<double>(bytes) / Kilo, 'f', 1) + " KB";
    } else if (bytes >= 0) {
        return QString::number(bytes) + " B";
    } else {
        return "NaN";
    }
}
