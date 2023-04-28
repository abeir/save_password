#include "account_manager.h"
#include "data/data_manager.h"
#include "session.h"
#include "util/sundry.h"
#include <QDebug>


namespace PROTECT_NAMESPACE {


AccountManager::AccountManager(QObject *parent)
    : QObject{parent}
{

}

AccountManager::~AccountManager()
{

}

AccountModel *AccountManager::accountModel()
{
    if(m_accountModel.IsEmpty()){
        auto memberId = SessionFactory::Instance().Current().Member().id();
        QList<AccountInfo> accounts = DataManager::Instance()->FindAccountByMemberId(memberId);
        m_accountModel.Appends(accounts);
    }
    return &m_accountModel;
}

void AccountManager::create(const QString &url, const QString &username, const QString &password, const QString &comment)
{
    auto memberId = SessionFactory::Instance().Current().Member().id();

    QString now = Sundry::Datetime::Now();
    AccountInfo acc{
        .url = url,
        .username{username},
        .password{password},
        .comment{comment},
        .createdAt{now},
        .updatedAt{now},
        .memberId = memberId
    };
    if(!DataManager::Instance()->SaveAccount(acc)){
        emit createFailed("save account failed");
        return;
    }
    bool oldIsEmpty = m_accountModel.IsEmpty();
    QList<AccountInfo> accounts = DataManager::Instance()->FindAccountByMemberId(memberId);
    m_accountModel.ReplaceAll(accounts);
    emit createSuccess();
    if(oldIsEmpty && !m_accountModel.IsEmpty()){
        emit emptyChanged();
    }
}

void AccountManager::update(quint32 id, const QString &url, const QString &username, const QString &password, const QString &comment)
{
    QString now = Sundry::Datetime::Now();
    AccountInfo acc{
        .url = url,
        .username{username},
        .password{password},
        .comment{comment},
        .updatedAt{now}
    };
    if(!DataManager::Instance()->UpdateAccount(acc, id)){
        emit updateFailed("update account failed");
        return;
    }
    auto memberId = SessionFactory::Instance().Current().Member().id();
    QList<AccountInfo> accounts = DataManager::Instance()->FindAccountByMemberId(memberId);
    m_accountModel.ReplaceAll(accounts);
    emit updateSuccess();
}

void AccountManager::remove(quint32 id)
{
    if(!DataManager::Instance()->ExistAccountById(id)){
        emit removeFailed("not found account");
        return;
    }
    DataManager::Instance()->RemoveAccount(id);
    auto memberId = SessionFactory::Instance().Current().Member().id();
    QList<AccountInfo> accounts = DataManager::Instance()->FindAccountByMemberId(memberId);
    m_accountModel.ReplaceAll(accounts);
    emit removeSuccess();

    if(m_accountModel.IsEmpty()){
        emit emptyChanged();
    }
}

bool AccountManager::isEmpty()
{
    auto memberId = SessionFactory::Instance().Current().Member().id();
    return DataManager::Instance()->CountAccountByMemberId(memberId) < 1;
}

}
