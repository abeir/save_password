#ifndef ACCOUNT_MODEL_H
#define ACCOUNT_MODEL_H

#include "global_defines.h"
#include "data/data_info.h"
#include <QAbstractListModel>
#include <QList>


namespace PROTECT_NAMESPACE {


class AccountModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RoleType
    {
        Id = Qt::UserRole + 1,
        Url,
        Username,
        Password,
        Comment,
        CreatedAt,
        UpdatedAt
    };

    explicit AccountModel(QObject *parent = nullptr);
    ~AccountModel();


    void Append(const AccountInfo &account);
    void Appends(const QList<AccountInfo> &accounts);
    void Remove(int index);
    void Replace(int index, const AccountInfo &account);
    void ReplaceAll(const QList<AccountInfo> &accounts);
    void Clear();

    bool IsEmpty();

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;

private:
    QList<AccountInfo> m_accounts;
};

}
#endif // ACCOUNT_MODEL_H
