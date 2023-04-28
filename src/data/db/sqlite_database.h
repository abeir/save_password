
#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include "global_defines.h"
#include "abstract_database.h"
#include <memory>

namespace PROTECT_NAMESPACE {

namespace Internal{
class SqliteDatabasePrivate;
}

class SqliteDatabase : public AbstractDatabase
{
public:
    SqliteDatabase(const QString &uri, const QVariantMap &options = {});
    virtual ~SqliteDatabase();

    void setDatabase(const QString &uri, const QVariantMap &options = {}) override;

    bool open() override;
    void close() override;
    bool isOpened() override;

    QStringList columns(const QString &tableName) override;
    QList<Row> select(const QString &sql) override;
    QList<Row> select(const QString &sql, const QVariant &arg) override;
    QList<Row> select(const QString &sql, const QVariant &arg1, const QVariant &arg2) override;
    QList<Row> select(const QString &sql, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3) override;
    QList<Row> select(const QString &sql, const QVariantList &args) override;
    Row selectOne(const QString &sql) override;
    Row selectOne(const QString &sql, const QVariant &arg) override;
    Row selectOne(const QString &sql, const QVariant &arg1, const QVariant &arg2) override;
    Row selectOne(const QString &sql, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3) override;
    Row selectOne(const QString &sql, const QVariantList &args) override;
    bool exec(const QString &sql) override;
    bool exec(const QString &sql, const QVariant &arg) override;
    bool exec(const QString &sql, const QVariant &arg1, const QVariant &arg2) override;
    bool exec(const QString &sql, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3) override;
    bool exec(const QString &sql, const QVariantList &args) override;
    long count(const QString &sql) override;
    long count(const QString &sql, const QVariant &arg) override;
    long count(const QString &sql, const QVariant &arg1, const QVariant &arg2) override;
    long count(const QString &sql, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3) override;
    long count(const QString &sql, const QVariantList &args) override;

    bool hasError() override;
    DatabaseError lastError() const override;

    inline DatabaseError createError(DatabaseErrorCode code, const char* err) { return {.code = code, .message = err}; }
    inline DatabaseError createError(DatabaseErrorCode code, const QString &err) { return {.code = code, .message = err}; }

private:
    std::unique_ptr<Internal::SqliteDatabasePrivate> m_private;
};

}
#endif // SQLITEDATABASE_H
