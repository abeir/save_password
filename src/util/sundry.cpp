#include "sundry.h"
#include <QDateTime>


namespace PROTECT_NAMESPACE {

namespace Sundry {

static QString DATETIME_FORMAT("yyyy-MM-dd hh:mm:ss");

QString Datetime::Now()
{
    return QDateTime::currentDateTimeUtc().toString(DATETIME_FORMAT);
}


}

}
