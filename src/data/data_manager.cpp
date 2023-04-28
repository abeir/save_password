
#include "data_manager.h"
#include "db_data_operator.h"
#include "data/db/sqlite_database.h"
#include <QDebug>

namespace PROTECT_NAMESPACE {


DataManager* DataManager::m_instance = nullptr;


DataManager::DataManager(QObject *parent)
    : QObject{parent}
{
}

DataManager::~DataManager()
{
}

void DataManager::init(std::shared_ptr<Settings> settings, QObject *parent)
{
    if(m_instance){
        return;
    }
    m_instance = new DataManager(parent);
    m_instance->m_settings = settings;

    qDebug() << "DatabaseUri:" << settings->DatabaseUri();

    std::unique_ptr<AbstractDatabase> db = std::make_unique<SqliteDatabase>(settings->DatabaseUri());
    m_instance->m_opt.reset(new DatabaseDataOperator(std::move(db)));

    m_instance->m_opt->migrate();
}

void DataManager::reset()
{
    if(!m_instance){
        return;
    }
    QObject* parent = m_instance->parent();
    std::shared_ptr<Settings> settings = m_instance->m_settings;

    delete m_instance;
    m_instance = nullptr;
    init(settings, parent);
}

void DataManager::destroy()
{
    if(!m_instance){
        return;
    }
    DataManager* obj = DataManager::m_instance;
    DataManager::m_instance = nullptr;
    obj->deleteLater();
}

DataManager *DataManager::Instance()
{
    return m_instance;
}

QList<AccountInfo> DataManager::FindAccountByMemberId(quint32 memberId)
{
    QVariantMap where;
    where["memberId"] = memberId;

    auto list = m_opt->selectAccounts(where);
    if(m_opt->hasError()){
        qWarning() << Q_FUNC_INFO << m_opt->getError();
        return {};
    }
    return list;
}

bool DataManager::SaveAccount(const AccountInfo &acc)
{
    m_opt->insertAccount(acc);
    if(m_opt->hasError()){
        qWarning() << Q_FUNC_INFO << m_opt->getError();
        return false;
    }
    return true;
}

bool DataManager::UpdateAccount(const AccountInfo &acc, quint32 id)
{
    m_opt->updateAccount(acc, id);
    if(m_opt->hasError()){
        qWarning() << Q_FUNC_INFO << m_opt->getError();
        return false;
    }
    return true;
}

bool DataManager::ExistAccountById(quint32 id)
{
    QVariantMap where;
    where["id"] = id;
    auto count = m_opt->countAccount(where);
    return count > 0;
}

void DataManager::RemoveAccount(quint32 id)
{
    m_opt->deleteAccount(id);
}

long DataManager::CountAccountByMemberId(quint32 memberId)
{
    QVariantMap where;
    where["member_id"] = memberId;
    return m_opt->countAccount(where);
}

std::optional<MemberInfo> DataManager::GetMemberByUsername(const QString &username)
{
    QVariantMap where;
    where["username"] = username;

    auto info = m_opt->selectMember(where);
    if(m_opt->hasError()){
        qWarning() << Q_FUNC_INFO << m_opt->getError();
        return {};
    }
    return info;
}

}
