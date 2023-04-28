
#include "data_info.h"


namespace PROTECT_NAMESPACE {


QString MemberInfo::toString() const
{
    return QString("MemberInfo{id: %1, username: \"%2\", password \"%3\":}").arg(QString::number(id), username, password);
}

QString AccountInfo::toString() const
{
    return QString("AccountInfo{id: %1, url: \"%2\", username: \"%3\", password: \"%4\", createdAt: \"%5\", updatedAt: \"%6\", comment: \"%7\", memberId: %8}")
        .arg(QString::number(id), url, username, password, createdAt, updatedAt, comment, QString::number(memberId));
}


}
