
#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "global_defines.h"
#include "data_info.h"
#include "data_operator.h"
#include "util/settings.h"
#include <QObject>
#include <QList>
#include <memory>


namespace PROTECT_NAMESPACE {

class DataManager : public QObject
{
    Q_OBJECT
public:
    ~DataManager();

    static void init(std::shared_ptr<Settings> settings, QObject *parent = nullptr);
    static void reset();
    static void destroy();

    static DataManager* Instance();

    QList<AccountInfo> FindAccountByMemberId(quint32 memberId);
    bool SaveAccount(const AccountInfo &);
    bool UpdateAccount(const AccountInfo &, quint32 id);
    bool ExistAccountById(quint32 id);
    void RemoveAccount(quint32 id);
    long CountAccountByMemberId(quint32 memberId);

    std::optional<MemberInfo> GetMemberByUsername(const QString &username);

private:
    DataManager(QObject *parent = nullptr);

    static DataManager* m_instance;
    std::unique_ptr<DataOperator> m_opt;
    std::shared_ptr<Settings> m_settings;
};

}
#endif // DATAMANAGER_H
