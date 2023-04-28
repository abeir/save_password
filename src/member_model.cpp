
#include "member_model.h"


namespace PROTECT_NAMESPACE {


MemberModel::MemberModel(QObject *parent)
    : QAbstractListModel{parent}
    , m_member{.id=0}
{

}

MemberModel::~MemberModel()
{

}

void MemberModel::Set(const MemberInfo &member)
{
    beginResetModel();
    m_member = member;
    endResetModel();
}

MemberInfo MemberModel::Current() const
{
    return m_member;
}

void MemberModel::Clear()
{
    beginResetModel();
    m_member = {.id = 0};
    endResetModel();
}


QHash<int, QByteArray> MemberModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[ID] = "ID";
    names[Username] = "Username";
    names[Password] = "Password";
    names[CreatedAt] = "CreatedAt";
    names[UpdatedAt] = "UpdatedAt";
    return names;
}

int MemberModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return IsEmpty() ? 0 : 1;
}

QVariant MemberModel::data(const QModelIndex &index, int role) const
{
    int rowIndex = index.row();
    if(rowIndex < 0 || rowIndex >= 1){
        return QVariant();
    }
    switch (role) {
    case ID:
        return m_member.id;
    case Username:
        return m_member.username;
    case Password:
        return m_member.password;
    case CreatedAt:
        return m_member.createdAt;
    case UpdatedAt:
        return m_member.updatedAt;
    default:
        return QVariant();
    }
}


}
