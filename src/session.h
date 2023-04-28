#ifndef DATA_SESSION_H
#define DATA_SESSION_H

#include "global_defines.h"
#include "member_model.h"
#include "data/data_info.h"
#include <QObject>
#include <memory>

namespace PROTECT_NAMESPACE {

class SessionFactory;

class Session : public QObject
{
    Q_OBJECT
public:
    Session(QObject *parent = nullptr);
    Session(Session &&);

    void Clear();

    Q_INVOKABLE bool HasMember();
    Q_INVOKABLE MemberModel& Member();

    void SetMember(const MemberModel &m);
    void SetMember(const MemberInfo &m);

private:
    Q_DISABLE_COPY(Session)
    std::unique_ptr<MemberModel> m_member;

    friend SessionFactory;
};


class SessionFactory
{
public:
    static SessionFactory& Instance();

    Session& Current();

private:
    SessionFactory();
    Q_DISABLE_COPY_MOVE(SessionFactory)

    static std::unique_ptr<SessionFactory> factory;
    std::unique_ptr<Session> m_session;
};

}
#endif
