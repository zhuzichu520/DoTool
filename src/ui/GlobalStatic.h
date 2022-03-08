#ifndef GLOBALSTATIC_H
#define GLOBALSTATIC_H

#include "QUIHelper.h"

Q_GLOBAL_STATIC(QUIHelper, uiHelper)

#define UIHelper uiHelper()

#endif // GLOBALSTATIC_H
