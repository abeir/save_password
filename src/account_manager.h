#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QObject>
#include "account_model.h"


namespace PROTECT_NAMESPACE {


class AccountManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(AccountModel* accountModel READ accountModel CONSTANT)
    Q_PROPERTY(bool empty READ isEmpty NOTIFY emptyChanged)
public:
    explicit AccountManager(QObject *parent = nullptr);
    ~AccountManager();

    AccountModel* accountModel();

    Q_INVOKABLE void create(const QString &url, const QString &username, const QString &password, const QString &comment);
    Q_INVOKABLE void update(quint32 id, const QString &url, const QString &username, const QString &password, const QString &comment);
    Q_INVOKABLE void remove(quint32 id);
    Q_INVOKABLE bool isEmpty();

signals:
    void emptyChanged();

    void createSuccess();
    void createFailed(const QString &msg);

    void updateSuccess();
    void updateFailed(const QString &msg);

    void removeSuccess();
    void removeFailed(const QString &msg);
private:
    AccountModel m_accountModel;
};

}
#endif // ACCOUNTMANAGER_H
