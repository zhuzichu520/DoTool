//#pragma execution_character_set("utf-8")
#ifndef GLOBALSTATIC_H
#define GLOBALSTATIC_H

#include "QUIHelper.h"
#include "QLogHelper.h"

Q_GLOBAL_STATIC(QUIHelper, uiHelper)
#define UIHelper uiHelper()

Q_GLOBAL_STATIC(QLogHelper, logHelper)
#define LogHelper logHelper()

#define LOGD(data) DLOG(INFO)<<logHelper()->toStdString(data)
#define LOGI(data) LOG(INFO)<<logHelper()->toStdString(data)
#define LOGW(data) LOG(WARNING)<<logHelper()->toStdString(data)
#define LOGE(data) LOG(ERROR)<<logHelper()->toStdString(data)

#endif // GLOBALSTATIC_H
