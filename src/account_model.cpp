#include "account_model.h"


namespace PROTECT_NAMESPACE {


AccountModel::AccountModel(QObject *parent) : QAbstractListModel(parent)
{

}

AccountModel::~AccountModel()
{
    m_accounts.clear();
}

void AccountModel::Append(const AccountInfo &account)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    m_accounts.emplaceBack(account);

    endInsertRows();
}

void AccountModel::Appends(const QList<AccountInfo> &accounts)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    for(const AccountInfo &acc : accounts){
        m_accounts.emplaceBack(acc);
    }

    endInsertRows();
}

void AccountModel::Remove(int index)
{
    beginRemoveRows(QModelIndex(), index, index);

    m_accounts.removeAt(index);

    endRemoveRows();
}

void AccountModel::Replace(int index, const AccountInfo &account)
{
    beginInsertRows(QModelIndex(), index, index);

    m_accounts[index] = account;

    endInsertRows();
}

void AccountModel::ReplaceAll(const QList<AccountInfo> &accounts)
{
    beginResetModel();
    m_accounts.clear();
    for(const AccountInfo &acc : accounts){
        m_accounts.emplaceBack(acc);
    }
    endResetModel();
}

void AccountModel::Clear()
{
    beginResetModel();

    m_accounts.clear();

    endResetModel();
}

bool AccountModel::IsEmpty()
{
    return m_accounts.empty();
}

QHash<int, QByteArray> AccountModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Id] = "Id";
    names[Url] = "Url";
    names[Username] = "Username";
    names[Password] = "Password";
    names[CreatedAt] = "CreatedAt";
    names[UpdatedAt] = "UpdatedAt";
    names[Comment] = "Comment";
    return names;
}

int AccountModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_accounts.size();
}

QVariant AccountModel::data(const QModelIndex &index, int role) const
{
    int rowIndex = index.row();
    if(rowIndex < 0 || rowIndex >= m_accounts.size()){
        return QVariant();
    }
    const AccountInfo &acc = m_accounts[rowIndex];
    switch (role) {
    case Id:
        return acc.id;
    case Url:
        return acc.url;
    case Username:
        return acc.username;
    case Password:
        return acc.password;
    case CreatedAt:
        return acc.createdAt;
    case UpdatedAt:
        return acc.updatedAt;
    case Comment:
        return acc.comment;
    default:
        return QVariant();
    }
}

}
