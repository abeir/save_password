
#include "sql_helper.h"

namespace PROTECT_NAMESPACE {


// #### SelectSqlHelper

SelectSqlHelper::SelectSqlHelper(const QString &select) : m_select{select}
{
}

SelectSqlHelper &SelectSqlHelper::setSelect(const QString &select)
{
    m_select = select;
    return *this;
}


SelectSqlHelper &SelectSqlHelper::addWhere(const QString &where)
{
    if(where.isEmpty()){
        return *this;
    }
    m_wheres << where;
    return *this;
}

SelectSqlHelper &SelectSqlHelper::addWhere(const QString &where, const QVariant &value)
{
    if(where.isEmpty()){
        return *this;
    }
    m_wheres << where;
    m_values << value;
    return *this;
}

SelectSqlHelper &SelectSqlHelper::addWhereLike(const QString &where, const QVariant &value)
{
    if(where.isEmpty()){
        return *this;
    }
    m_wheres << where;
    m_values << "%" + value.toString() + "%";
    return *this;
}

QString SelectSqlHelper::toSql() const
{
    if(m_wheres.isEmpty()){
        return m_select;
    }
    return QString("%1 where %2").arg(m_select, m_wheres.join(" and "));
}


// #### InsertSqlHelper

InsertSqlHelper::InsertSqlHelper(const QString &table) : m_table{table}
{
}

InsertSqlHelper &InsertSqlHelper::setTable(const QString &table)
{
    m_table = table;
    return *this;
}

InsertSqlHelper &InsertSqlHelper::addColumn(const QString &column, const QVariant &value)
{
    if(column.isEmpty()){
        return *this;
    }
    m_columns << column;
    m_values << value;
    return *this;
}

QString InsertSqlHelper::toSql() const
{
    if(m_table.isEmpty() || m_columns.isEmpty()){
        return {};
    }
    QStringList placeholders;
    for(int i=0; i<m_columns.count(); i++){
        placeholders << "?";
    }
    return QString("insert into %1(%2) values(%3)").arg(m_table, m_columns.join(","), placeholders.join(","));
}


// #### UpdateSqlHelper

UpdateSqlHelper::UpdateSqlHelper(const QString &table) : m_table{table}
{
}

UpdateSqlHelper &UpdateSqlHelper::setTable(const QString &table)
{
    m_table = table;
    return *this;
}

UpdateSqlHelper &UpdateSqlHelper::addColumn(const QString &column, const QVariant &value)
{
    if(column.isEmpty()){
        return *this;
    }
    m_columns << column;
    m_values << value;
    return *this;
}

UpdateSqlHelper &UpdateSqlHelper::addWhere(const QString &where)
{
    if(where.isEmpty()){
        return *this;
    }
    m_wheres << where;
    return *this;
}

UpdateSqlHelper &UpdateSqlHelper::addWhere(const QString &where, const QVariant &value)
{
    if(where.isEmpty()){
        return *this;
    }
    m_wheres << where;
    m_values << value.toString();
    return *this;
}

UpdateSqlHelper &UpdateSqlHelper::addWhereLike(const QString &where, const QVariant &value)
{
    if(where.isEmpty()){
        return *this;
    }
    m_wheres << where;
    m_values << "%" + value.toString() + "%";
    return *this;
}

QString UpdateSqlHelper::toSql() const
{
    if(m_table.isEmpty() || m_columns.isEmpty()){
        return {};
    }
    QStringList columns;
    for(auto &col : m_columns){
        columns << col + "=?";
    }

    return QString("update %1 set %2 where %3").arg(m_table, columns.join(","), m_wheres.join(" and "));
}


// #### DeleteSqlHelper

DeleteSqlHelper::DeleteSqlHelper(const QString &table) : m_table{table}
{
}

DeleteSqlHelper &DeleteSqlHelper::setTable(const QString &table)
{
    m_table = table;
    return *this;
}

DeleteSqlHelper &DeleteSqlHelper::addWhere(const QString &where)
{
    if(where.isEmpty()){
        return *this;
    }
    m_wheres << where;
    return *this;
}

DeleteSqlHelper &DeleteSqlHelper::addWhere(const QString &where, const QVariant &value)
{
    if(where.isEmpty()){
        return *this;
    }
    m_wheres << where;
    m_values << value.toString();
    return *this;
}

DeleteSqlHelper &DeleteSqlHelper::addWhereLike(const QString &where, const QVariant &value)
{
    if(where.isEmpty()){
        return *this;
    }
    m_wheres << where;
    m_values << "%" + value.toString() + "%";
    return *this;
}

QString DeleteSqlHelper::toSql() const
{
    if(m_table.isEmpty()){
        return {};
    }
    return QString("delete from %1 where %2").arg(m_table, m_wheres.join(" and "));
}


}
