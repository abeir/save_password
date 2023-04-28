
#ifndef MEMBERMODEL_H
#define MEMBERMODEL_H

#include "global_defines.h"
#include "data/data_info.h"
#include <QAbstractListModel>


namespace PROTECT_NAMESPACE {


class MemberModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(quint32 id READ id)
    Q_PROPERTY(QString username READ username)
    Q_PROPERTY(QString password READ password)
    Q_PROPERTY(QString createdAt READ createdAt)
    Q_PROPERTY(QString updatedAt READ updatedAt)
public:
    enum RoleType
    {
        ID = Qt::UserRole + 1,
        Username,
        Password,
        CreatedAt,
        UpdatedAt
    };

    explicit MemberModel(QObject *parent = nullptr);
    ~MemberModel();

    void Set(const MemberInfo &member);
    MemberInfo Current() const;
    void Clear();
    inline bool IsEmpty() const { return m_member.id <= 0; }

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    inline quint32 id() const { return m_member.id; }
    inline QString username() const { return m_member.username; }
    inline QString password() const { return m_member.password; }
    inline QString createdAt() const { return m_member.createdAt; }
    inline QString updatedAt() const { return m_member.updatedAt; }
private:
    MemberInfo m_member;
};

}
#endif // MEMBERMODEL_H
