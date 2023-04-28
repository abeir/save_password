
#ifndef DATAOPERATOR_H
#define DATAOPERATOR_H

#include "global_defines.h"
#include "data_info.h"
#include "data/db/abstract_database.h"
#include <QList>
#include <QVariantMap>
#include <QObject>
#include <QString>
#include <memory>


namespace PROTECT_NAMESPACE {


class DataOperateError
{
public:
    inline void setError(const QString &err) { m_error = err; }
    inline QString getError() { return m_error; }
    inline bool hasError() { return !m_error.isEmpty(); }
private:
    QString m_error;
};


class DataOperator : public DataOperateError
{
public:
    virtual ~DataOperator(){}

    virtual std::optional<AccountInfo> selectAccount(const QVariantMap &where) = 0;
    virtual QList<AccountInfo> selectAccounts(const QVariantMap &where = QVariantMap()) = 0;
    virtual void insertAccount(const AccountInfo &acc) = 0;
    virtual void updateAccount(const AccountInfo &acc, quint32 id) = 0;
    virtual void deleteAccount(quint32 id) = 0;
    virtual long countAccount(const QVariantMap &where) = 0;

    virtual std::optional<MemberInfo> selectMember(const QVariantMap &where) = 0;
    virtual void insertMember(const MemberInfo &member) = 0;
    virtual void updateMember(const MemberInfo &member, quint32 id) = 0;
    virtual void deleteMember(quint32 id) = 0;
    virtual long countMember(const QVariantMap &where) = 0;

    virtual void migrate() = 0;

    inline void setDatabase(std::unique_ptr<AbstractDatabase> db){ m_database = std::move(db); }
    inline AbstractDatabase* database() { return m_database.get(); }
private:
    std::unique_ptr<AbstractDatabase> m_database;
};

}
#endif // DATAOPERATOR_H
