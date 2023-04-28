#include "member_manager.h"
#include "data/data_manager.h"
#include "util/cipher.h"

namespace PROTECT_NAMESPACE {


MemberManager::MemberManager(QObject *parent)
    : QObject{parent}
{

}

MemberManager::~MemberManager() = default;

void MemberManager::login(const QString &username, const QString &password)
{
    if(username.isEmpty()){
        emit loginFailed("username is empty");
        return;
    }
    if(password.isEmpty()){
        emit loginFailed("password is empty");
        return;
    }
    auto member = DataManager::Instance()->GetMemberByUsername(username);
    if(!member.has_value()){
        emit loginFailed("username not found");
        return;
    }
    if(Cipher::obfuscate(password.toUtf8(), "") != member.value().password){
        emit loginFailed("password invalid");
        return;
    }
    SessionFactory::Instance().Current().SetMember(member.value());
    emit loginSuccess(QString());
    emit loggedInChanged();
}

void MemberManager::logout()
{
    SessionFactory::Instance().Current().Clear();
    emit logoutSuccess();
    emit loggedInChanged();
}

Session* MemberManager::session() const
{
    return &SessionFactory::Instance().Current();
}


bool MemberManager::isLoggedIn()
{
    return SessionFactory::Instance().Current().HasMember();
}

}
