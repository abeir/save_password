
#include "sqlite_database.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>


#define SQLITE_CONNECTION_NAME "protect_sqlite3"

namespace PROTECT_NAMESPACE {

namespace Internal{
    class SqliteDatabasePrivate
    {
    public:
        explicit SqliteDatabasePrivate(SqliteDatabase* parent);
        ~SqliteDatabasePrivate();

        QList<AbstractDatabase::Row> fetchAll(QSqlQuery &query);
        AbstractDatabase::Row fetchOne(QSqlQuery &query);
        long fetchCount(QSqlQuery &query);

        inline void setError(AbstractDatabase::DatabaseErrorCode code, const char* err) { error = d->createError(code, err); }
        inline void setError(AbstractDatabase::DatabaseErrorCode code, const QString &err) { error = d->createError(code, err); }
        inline void setError(AbstractDatabase::DatabaseErrorCode code, const QSqlError &err) { error = d->createError(code, err.isValid() ? err.text() : ""); }

        inline void clearError() { error.code = AbstractDatabase::NoError; error.message = QString(); }

        QString uri;
        QSqlDatabase db;
        AbstractDatabase::DatabaseError error;
    private:
        SqliteDatabase *d;
    };

    SqliteDatabasePrivate::SqliteDatabasePrivate(SqliteDatabase* parent)
        : d(parent)
        , error{AbstractDatabase::NoError, QString()}
    {
        const QString connectionName(SQLITE_CONNECTION_NAME);
        if(QSqlDatabase::contains(connectionName)){
            db = QSqlDatabase::database(connectionName, false);
        }else{
            db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        }
    }

    SqliteDatabasePrivate::~SqliteDatabasePrivate()
    {
        if(db.isOpen()){
            db.close();
        }
    }

    QList<AbstractDatabase::Row> SqliteDatabasePrivate::fetchAll(QSqlQuery &query)
    {
        QList<AbstractDatabase::Row> result;
        while(query.next()){
            AbstractDatabase::Row row;
            QSqlRecord record = query.record();
            for(int i=0; i<record.count(); i++){
                row << record.value(i);
            }
            result << row;
        }
        return result;
    }

    AbstractDatabase::Row SqliteDatabasePrivate::fetchOne(QSqlQuery &query)
    {
        if(query.next()){
            AbstractDatabase::Row row;
            QSqlRecord record = query.record();
            for(int i=0; i<record.count(); i++){
                row << record.value(i);
            }
            return row;
        }
        return {};
    }

    long SqliteDatabasePrivate::fetchCount(QSqlQuery &query)
    {
        if(query.next()){
            return query.value(0).toLongLong();
        }
        return 0;
    }
}

using namespace Internal;

// SqliteDatabase

SqliteDatabase::SqliteDatabase(const QString &uri, const QVariantMap &options) : m_private(new SqliteDatabasePrivate(this))
{
    Q_UNUSED(options)
    m_private->uri = uri;
}

void SqliteDatabase::setDatabase(const QString &uri, const QVariantMap &options)
{
    Q_UNUSED(options)
    m_private->uri = uri;
}

SqliteDatabase::~SqliteDatabase() = default;

bool SqliteDatabase::open()
{
    m_private->clearError();
    if(m_private->uri.isEmpty()){
        m_private->setError(AbstractDatabase::OpenError, "invalid uri");
        return false;
    }

    if(!m_private->db.isValid()){
        m_private->setError(AbstractDatabase::OpenError, "invalid driver:" + m_private->db.driverName());
        return false;
    }
    if(m_private->db.isOpen()){
        return true;
    }
    m_private->db.setDatabaseName(m_private->uri);
    if(!m_private->db.open()){
        m_private->setError(AbstractDatabase::OpenError, m_private->db.lastError());
        return false;
    }
    qDebug() << "open:" << m_private->uri;
    return true;
}

void SqliteDatabase::close()
{
    m_private->db.close();
}

bool SqliteDatabase::isOpened()
{
    return m_private->db.isOpen();
}

QStringList SqliteDatabase::columns(const QString &tableName)
{
    QSqlRecord record = m_private->db.record(tableName);
    QStringList fields;
    for(int i=0; i<record.count(); i++){
        fields << record.fieldName(i);
    }
    return fields;
}

QList<AbstractDatabase::Row> SqliteDatabase::select(const QString &sql)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.exec(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    return m_private->fetchAll(query);
}

QList<AbstractDatabase::Row> SqliteDatabase::select(const QString &sql, const QVariant &arg)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    query.addBindValue(arg);
    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    return m_private->fetchAll(query);
}

QList<AbstractDatabase::Row> SqliteDatabase::select(const QString &sql, const QVariant &arg1, const QVariant &arg2)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    query.addBindValue(arg1);
    query.addBindValue(arg2);
    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    return m_private->fetchAll(query);
}

QList<AbstractDatabase::Row> SqliteDatabase::select(const QString &sql, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    query.addBindValue(arg1);
    query.addBindValue(arg2);
    query.addBindValue(arg3);
    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    return m_private->fetchAll(query);
}

QList<AbstractDatabase::Row> SqliteDatabase::select(const QString &sql, const QVariantList &args)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    for(auto &arg : args){
        query.addBindValue(arg);
    }
    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    return m_private->fetchAll(query);
}

AbstractDatabase::Row SqliteDatabase::selectOne(const QString &sql)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.exec(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    return m_private->fetchOne(query);
}

AbstractDatabase::Row SqliteDatabase::selectOne(const QString &sql, const QVariant &arg)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    query.addBindValue(arg);

    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    return m_private->fetchOne(query);
}

AbstractDatabase::Row SqliteDatabase::selectOne(const QString &sql, const QVariant &arg1, const QVariant &arg2)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    query.addBindValue(arg1);
    query.addBindValue(arg2);

    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    return m_private->fetchOne(query);
}

AbstractDatabase::Row SqliteDatabase::selectOne(const QString &sql, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    query.addBindValue(arg1);
    query.addBindValue(arg2);
    query.addBindValue(arg3);

    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    return m_private->fetchOne(query);
}

AbstractDatabase::Row SqliteDatabase::selectOne(const QString &sql, const QVariantList &args)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    for(auto &arg : args){
        query.addBindValue(arg);
    }
    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return {};
    }
    return m_private->fetchOne(query);
}

bool SqliteDatabase::exec(const QString &sql)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.exec(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return false;
    }
    return true;
}

bool SqliteDatabase::exec(const QString &sql, const QVariant &arg)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return false;
    }
    query.addBindValue(arg);
    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return false;
    }
    return true;
}

bool SqliteDatabase::exec(const QString &sql, const QVariant &arg1, const QVariant &arg2)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return false;
    }
    query.addBindValue(arg1);
    query.addBindValue(arg2);
    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return false;
    }
    return true;
}

bool SqliteDatabase::exec(const QString &sql, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return false;
    }
    query.addBindValue(arg1);
    query.addBindValue(arg2);
    query.addBindValue(arg3);
    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return false;
    }
    return true;
}

bool SqliteDatabase::exec(const QString &sql, const QVariantList &args)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return false;
    }
    for(auto &arg : args){
        query.addBindValue(arg);
    }
    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return false;
    }
    return true;
}

long SqliteDatabase::count(const QString &sql)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.exec(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return false;
    }
    return m_private->fetchCount(query);
}

long SqliteDatabase::count(const QString &sql, const QVariant &arg)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return -1;
    }
    query.addBindValue(arg);
    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return -1;
    }
    return m_private->fetchCount(query);
}

long SqliteDatabase::count(const QString &sql, const QVariant &arg1, const QVariant &arg2)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return -1;
    }
    query.addBindValue(arg1);
    query.addBindValue(arg2);
    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return -1;
    }
    return m_private->fetchCount(query);
}

long SqliteDatabase::count(const QString &sql, const QVariant &arg1, const QVariant &arg2, const QVariant &arg3)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return -1;
    }
    query.addBindValue(arg1);
    query.addBindValue(arg2);
    query.addBindValue(arg3);
    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return -1;
    }
    return m_private->fetchCount(query);
}

long SqliteDatabase::count(const QString &sql, const QVariantList &args)
{
    m_private->clearError();

    QSqlQuery query(m_private->db);
    if(!query.prepare(sql)){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return -1;
    }
    for(auto &arg : args){
        query.addBindValue(arg);
    }
    if(!query.exec()){
        m_private->setError(AbstractDatabase::SelectError, query.lastError());
        return -1;
    }
    return m_private->fetchCount(query);
}

bool SqliteDatabase::hasError()
{
    return m_private->error.code != AbstractDatabase::NoError;
}

AbstractDatabase::DatabaseError SqliteDatabase::lastError() const
{
    return m_private->error;
}



}
