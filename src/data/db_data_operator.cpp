
#include "db_data_operator.h"
#include "data/db/sql_helper.h"
#include "util/cipher.h"
#include <QDebug>
#include <QList>
#include <QDateTime>


namespace PROTECT_NAMESPACE {


DatabaseDataOperator::DatabaseDataOperator(std::unique_ptr<AbstractDatabase> db)
{
    setDatabase(std::move(db));
    database()->open();
    if(database()->hasError()){
        qDebug() << "open failed:" << database()->lastError();
    }
}

DatabaseDataOperator::~DatabaseDataOperator()
{
    database()->close();
}

std::optional<Protect::AccountInfo> DatabaseDataOperator::selectAccount(const QVariantMap &where)
{
    SelectSqlHelper helper("select id,url,username,password,created_at,updated_at,comment,member_id from protect_account");
    if(where.contains("id")){
        helper.addWhere("id = ?", where["id"]);
    }
    if(where.contains("username")){
        helper.addWhere("username = ?", where["username"]);
    }
    auto db = database();
    AbstractDatabase::Row row = db->selectOne(helper.toSql(), helper.values());
    if(db->hasError()){
        qWarning() << Q_FUNC_INFO << db->lastError() << "| sql:" << helper.toSql() << ", values:" << helper.values();
        return {};
    }
    return AccountInfo {
        .id = row[0].toUInt(),
        .url = row[1].toString(),
        .username = row[2].toString(),
        .password = row[3].toString(),
        .comment = row[4].toString(),
        .createdAt = row[5].toString(),
        .updatedAt = row[6].toString(),
        .memberId = row[7].toUInt()
    };
}

QList<AccountInfo> DatabaseDataOperator::selectAccounts(const QVariantMap &where)
{
    SelectSqlHelper helper("select id,url,username,password,comment,created_at,updated_at,member_id from protect_account");
    if(where.contains("memberId")){
        helper.addWhere("member_id = ?", where["memberId"]);
    }
    if(where.contains("url")){
        helper.addWhereLike("url like ?", where["url"]);
    }
    if(where.contains("username")){
        helper.addWhere("username = ?", where["username"]);
    }

    auto db = database();
    QList<AbstractDatabase::Row> ls = db->select(helper.toSql(), helper.values());
    if(db->hasError()){
        qWarning() << Q_FUNC_INFO << db->lastError() << "| sql:" << helper.toSql() << ", values:" << helper.values();
        return {};
    }

    QList<AccountInfo> accounts;
    for(auto &row : ls){
        accounts << AccountInfo {
            .id = row[0].toUInt(),
            .url = row[1].toString(),
            .username = row[2].toString(),
            .password = row[3].toString(),
            .comment = row[4].toString(),
            .createdAt = row[5].toString(),
            .updatedAt = row[6].toString(),
            .memberId = row[7].toUInt()
        };
    }
    return accounts;
}

void DatabaseDataOperator::insertAccount(const AccountInfo &acc)
{
    InsertSqlHelper helper("protect_account");
    helper.addColumn("url", acc.url)
        .addColumn("username", acc.username)
        .addColumn("password", acc.password)
        .addColumn("created_at", acc.createdAt)
        .addColumn("updated_at", acc.updatedAt)
        .addColumn("comment", acc.comment)
        .addColumn("member_id", acc.memberId);

    auto db = database();
    db->exec(helper.toSql(), helper.values());
    if(db->hasError()){
        qWarning() << Q_FUNC_INFO << db->lastError() << "| sql:" << helper.toSql() << ", values:" << helper.values();
    }
}

void DatabaseDataOperator::updateAccount(const AccountInfo &acc, quint32 id)
{
    UpdateSqlHelper helper("protect_account");
    if(!acc.url.isEmpty()){
        helper.addColumn("url", acc.url);
    }
    if(!acc.username.isEmpty()){
        helper.addColumn("username", acc.username);
    }
    if(!acc.password.isEmpty()){
        helper.addColumn("password", acc.password);
    }
    if(!acc.updatedAt.isEmpty()){
        helper.addColumn("updated_at", acc.updatedAt);
    }
    helper.addWhere("id=?", id);

    auto db = database();
    db->exec(helper.toSql(), helper.values());
    if(db->hasError()){
        qWarning() << Q_FUNC_INFO << db->lastError() << "| sql:" << helper.toSql() << ", values:" << helper.values();
    }
}

void DatabaseDataOperator::deleteAccount(quint32 id)
{
    QString sql("delete from protect_account where id=?");
    auto db = database();
    db->exec(sql, id);
    if(db->hasError()){
        qWarning() << Q_FUNC_INFO << db->lastError() << "| sql:" << sql << ", values:" << id;
    }
}

long DatabaseDataOperator::countAccount(const QVariantMap &where)
{
    SelectSqlHelper helper("select count(*) from protect_account");
    if(where.contains("id")){
        helper.addWhere("id=?", where["id"]);
    }
    if(where.contains("url")){
        helper.addWhere("url=?", where["url"]);
    }
    if(where.contains("username")){
        helper.addWhere("username=?", where["username"]);
    }
    if(where.contains("member_id")){
        helper.addWhere("member_id=?", where["member_id"]);
    }
    auto db = database();
    auto count = db->count(helper.toSql(), helper.values());
    if(db->hasError()){
        qWarning() << Q_FUNC_INFO << db->lastError() << "| sql:" << helper.toSql() << ", values:" << helper.values();
    }
    return count;
}

std::optional<MemberInfo> DatabaseDataOperator::selectMember(const QVariantMap &where)
{
    SelectSqlHelper helper("select id,username,password,created_at,updated_at from protect_member");
    if(where.contains("id")){
        helper.addWhere("id = ?", where["id"]);
    }
    if(where.contains("username")){
        helper.addWhere("username = ?", where["username"]);
    }
    auto db = database();
    AbstractDatabase::Row row = db->selectOne(helper.toSql(), helper.values());
    if(db->hasError()){
        qWarning() << Q_FUNC_INFO << db->lastError() << "| sql:" << helper.toSql() << ", values:" << helper.values();
        return {};
    }
    return MemberInfo {
        .id = row[0].toUInt(),
        .username = row[1].toString(),
        .password = row[2].toString(),
        .createdAt = row[3].toString(),
        .updatedAt = row[4].toString()
    };
}

void DatabaseDataOperator::insertMember(const MemberInfo &member)
{
    InsertSqlHelper helper("protect_member");
    helper.addColumn("username", member.username)
        .addColumn("password", member.password)
        .addColumn("created_at", member.createdAt)
        .addColumn("updated_at", member.updatedAt);

    auto db = database();
    db->exec(helper.toSql(), helper.values());
    if(db->hasError()){
        qWarning() << Q_FUNC_INFO << db->lastError() << "| sql:" << helper.toSql() << ", values:" << helper.values();
    }
}

void DatabaseDataOperator::updateMember(const MemberInfo &member, quint32 id)
{
    UpdateSqlHelper helper("protect_member");

    if(!member.username.isEmpty()){
        helper.addColumn("username", member.username);
    }
    if(!member.password.isEmpty()){
        helper.addColumn("password", member.password);
    }
    if(!member.updatedAt.isEmpty()){
        helper.addColumn("updated_at", member.updatedAt);
    }
    helper.addWhere("id=?", id);

    auto db = database();
    db->exec(helper.toSql(), helper.values());
    if(db->hasError()){
        qWarning() << Q_FUNC_INFO << db->lastError() << "| sql:" << helper.toSql() << ", values:" << helper.values();
    }
}

void DatabaseDataOperator::deleteMember(quint32 id)
{
    QString sql("delete from protect_member where id=?");
    auto db = database();
    db->exec(sql, id);
    if(db->hasError()){
        qWarning() << Q_FUNC_INFO << db->lastError() << "| sql:" << sql << ", values:" << id;
    }
}

long DatabaseDataOperator::countMember(const QVariantMap &where)
{
    SelectSqlHelper helper("select count(*) from protect_member");
    if(where.contains("id")){
        helper.addWhere("id = ?", where["id"]);
    }
    if(where.contains("username")){
        helper.addWhere("username = ?", where["username"]);
    }
    auto db = database();
    auto count = db->count(helper.toSql(), helper.values());
    if(db->hasError()){
        qWarning() << Q_FUNC_INFO << db->lastError() << "| sql:" << helper.toSql() << ", values:" << helper.values();
    }
    return count;
}

#define __CREATE_MEMBER_TABLE \
    "create table if not exists protect_member(" \
        "id integer primary key autoincrement," \
        "username text," \
        "password text," \
        "created_at text," \
        "updated_at text" \
    ")"

#define __CREATE_ACCOUNT_TABLE \
    "create table if not exists protect_account(" \
        "id integer primary key autoincrement," \
        "url text," \
        "username text," \
        "password text," \
        "comment text," \
        "member_id integer," \
        "created_at text," \
        "updated_at text" \
    ")"

void DatabaseDataOperator::migrate()
{
    QString memberTablel(__CREATE_MEMBER_TABLE);
    auto db = database();
    db->exec(memberTablel);
    if(db->hasError()){
        qWarning() << Q_FUNC_INFO << db->lastError() << "| create table protect_member";
        return;
    }
    QString accountTable(__CREATE_ACCOUNT_TABLE);
    db->exec(accountTable);
    if(db->hasError()){
        qWarning() << Q_FUNC_INFO << db->lastError() << "| create table protect_account";
        return;
    }

    QString countMember("select count(*) from protect_member");
    auto count = db->count(countMember);
    if(db->hasError()){
        qWarning() << Q_FUNC_INFO << db->lastError() << "| sql:" << countMember;
        return;
    }
    if(count == 0){
        QString now = QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh::mm::ss");
        MemberInfo member{
            .username{"abeir"},
            .password{Cipher::obfuscate("abeir", "")},
            .createdAt{now},
            .updatedAt{now}
        };
        insertMember(member);
    }
}

}
