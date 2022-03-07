#include "ScreenImageProvider.h"

QPixmap ScreenImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize){
    m_screen = qApp->screens().at(id.toInt());
    return m_screen->grabWindow(0);
}
