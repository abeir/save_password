
#ifndef SQLITEDATAOPERATOR_H
#define SQLITEDATAOPERATOR_H

#include "global_defines.h"
#include "data_operator.h"
#include "data/db/abstract_database.h"
#include <QObject>


namespace PROTECT_NAMESPACE{

class DatabaseDataOperator : public DataOperator
{
public:
    explicit DatabaseDataOperator(std::unique_ptr<AbstractDatabase> db);
    ~DatabaseDataOperator();

    std::optional<AccountInfo> selectAccount(const QVariantMap &where) override;
    QList<AccountInfo> selectAccounts(const QVariantMap &where) override;
    void insertAccount(const AccountInfo &acc) override;
    void updateAccount(const AccountInfo &acc, quint32 id) override;
    void deleteAccount(quint32 id) override;
    long countAccount(const QVariantMap &where) override;

    std::optional<MemberInfo> selectMember(const QVariantMap &where) override;
    void insertMember(const MemberInfo &member) override;
    void updateMember(const MemberInfo &member, quint32 id) override;
    void deleteMember(quint32 id) override;
    long countMember(const QVariantMap &where) override;

    void migrate() override;
};

}
#endif // SQLITEDATAOPERATOR_H
