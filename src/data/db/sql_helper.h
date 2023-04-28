
#ifndef SQLHELPER_H
#define SQLHELPER_H

#include "global_defines.h"
#include <QString>
#include <QStringList>
#include <QVariant>


namespace PROTECT_NAMESPACE {


class SelectSqlHelper
{
public:
    explicit SelectSqlHelper(const QString &select = QString());

    SelectSqlHelper& setSelect(const QString &select);

    SelectSqlHelper& addWhere(const QString &where);
    SelectSqlHelper& addWhere(const QString &where, const QVariant &value);
    SelectSqlHelper& addWhereLike(const QString &where, const QVariant &value);

    QString toSql() const;
    inline QVariantList values() const { return m_values; }

private:
    QString m_select;
    QStringList m_wheres;
    QVariantList m_values;
};

class InsertSqlHelper
{
public:
    explicit InsertSqlHelper(const QString &table = QString());

    InsertSqlHelper& setTable(const QString &table);
    InsertSqlHelper& addColumn(const QString &column, const QVariant &value);

    QString toSql() const;
    inline QVariantList values() const { return m_values; }

private:
    QString m_table;
    QStringList m_columns;
    QVariantList m_values;
};

class UpdateSqlHelper
{
public:
    explicit UpdateSqlHelper(const QString &table = QString());

    UpdateSqlHelper& setTable(const QString &table);
    UpdateSqlHelper& addColumn(const QString &column, const QVariant &value);

    UpdateSqlHelper& addWhere(const QString &where);
    UpdateSqlHelper& addWhere(const QString &where, const QVariant &value);
    UpdateSqlHelper& addWhereLike(const QString &where, const QVariant &value);

    QString toSql() const;
    inline QVariantList values() const { return m_values; }
private:
    QString m_table;
    QStringList m_columns;
    QStringList m_wheres;
    QVariantList m_values;
};

class DeleteSqlHelper
{
public:
    explicit DeleteSqlHelper(const QString &table = QString());

    DeleteSqlHelper& setTable(const QString &table);

    DeleteSqlHelper& addWhere(const QString &where);
    DeleteSqlHelper& addWhere(const QString &where, const QVariant &value);
    DeleteSqlHelper& addWhereLike(const QString &where, const QVariant &value);

    QString toSql() const;
    inline QVariantList values() const { return m_values; }
private:
    QString m_table;
    QStringList m_wheres;
    QVariantList m_values;
};

}
#endif // SQLHELPER_H
