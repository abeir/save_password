
#ifndef ABSTRACT_DATABASE_H
#define ABSTRACT_DATABASE_H

#include "global_defines.h"
#include <QString>
#include <QVariantMap>
#include <QStringList>
#include <QList>
#include <QDebug>


namespace PROTECT_NAMESPACE {

class AbstractDatabase
{
public:
    typedef QVariant Cell;
    typedef QList<Cell> Row;

    enum DatabaseErrorCode
    {
        NoError, OpenError, SelectError, ExecError
    };

    struct DatabaseError
    {
        DatabaseErrorCode code;
        QString message;
    };
    virtual ~AbstractDatabase(){}

    virtual void setDatabase(const QString &uri, const QVariantMap &options = {}) = 0;

    virtual bool open() = 0;
    virtual void close() = 0;

    virtual bool isOpened() = 0;

    virtual QStringList columns(const QString &tableName) = 0;

    virtual QList<Row> select(const QString &sql) = 0;
    virtual QList<Row> select(const QString &sql, const QVariant &arg) = 0;
    virtual QList<Row> select(const QString &sql, const QVariant &arg1, const QVariant &arg2) = 0;
    virtual QList<Row> select(const QString &sql, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3) = 0;
    virtual QList<Row> select(const QString &sql, const QVariantList &args) = 0;

    virtual Row selectOne(const QString &sql) = 0;
    virtual Row selectOne(const QString &sql, const QVariant &arg) = 0;
    virtual Row selectOne(const QString &sql, const QVariant &arg1, const QVariant &arg2) = 0;
    virtual Row selectOne(const QString &sql, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3) = 0;
    virtual Row selectOne(const QString &sql, const QVariantList &args) = 0;

    virtual bool exec(const QString &sql) = 0;
    virtual bool exec(const QString &sql, const QVariant &arg) = 0;
    virtual bool exec(const QString &sql, const QVariant &arg1, const QVariant &arg2) = 0;
    virtual bool exec(const QString &sql, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3) = 0;
    virtual bool exec(const QString &sql, const QVariantList &args) = 0;

    virtual long count(const QString &sql) = 0;
    virtual long count(const QString &sql, const QVariant &arg) = 0;
    virtual long count(const QString &sql, const QVariant &arg1, const QVariant &arg2) = 0;
    virtual long count(const QString &sql, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3) = 0;
    virtual long count(const QString &sql, const QVariantList &args) = 0;

    virtual bool hasError() = 0;
    virtual DatabaseError lastError() const = 0;
};


inline QDebug &operator<<(QDebug& debug, const AbstractDatabase::DatabaseError &err)
{
    return debug.nospace() << "DatabaseError(code=" << (int)err.code << ", message=" << err.message << ") ";
}

}

#endif // ABSTRACT_DATABASE_H
