#ifndef MEMBER_MANAGER_H
#define MEMBER_MANAGER_H

#include <QObject>
#include <QString>
#include "global_defines.h"
#include "session.h"


namespace PROTECT_NAMESPACE {


class MemberManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isLoggedIn READ isLoggedIn NOTIFY loggedInChanged)
    Q_PROPERTY(Session* session READ session CONSTANT)
public:

    explicit MemberManager(QObject *parent = nullptr);
    ~MemberManager();

    Q_INVOKABLE void login(const QString &username, const QString &password);
    Q_INVOKABLE void logout();

    Session* session() const;

    bool isLoggedIn();

signals:
    void loggedInChanged();

    void loginSuccess(const QString &token);
    void loginFailed(const QString &msg);

    void logoutSuccess();
};

}
#endif // MEMBER_MANAGER_H
