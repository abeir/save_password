
#ifndef DATAINFO_H
#define DATAINFO_H


#include "global_defines.h"
#include <QString>
#include <QSharedPointer>
#include <QDebug>


namespace PROTECT_NAMESPACE {


class MemberInfo
{
public:
    quint32 id;
    QString username;
    QString password;
    QString createdAt;
    QString updatedAt;

    QString toString() const;
};


class AccountInfo
{
public:
    quint32 id;
    QString url;
    QString username;
    QString password;
    QString comment;
    QString createdAt;
    QString updatedAt;
    quint32 memberId;

    QString toString() const;
};


inline QDebug& operator<<(QDebug& debug, const MemberInfo &info)
{
    return debug << info.toString();
}

inline QDebug& operator<<(QDebug& debug, const AccountInfo &info)
{
    return debug << info.toString();
}


}
#endif // DATAINFO_H
