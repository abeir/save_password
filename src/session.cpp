#include "session.h"

namespace PROTECT_NAMESPACE {


// #### Session

Session::Session(QObject *parent) : QObject(parent)
{

};

Session::Session(Session &&session)
{
    m_member = std::move(session.m_member);
}

void Session::Clear()
{
    m_member.release();
}

bool Session::HasMember()
{
    return m_member && m_member->id() > 0;
}

MemberModel &Session::Member()
{
    return *m_member;
}

void Session::SetMember(const MemberModel &m)
{
    MemberInfo info{
        .id = m.id(),
        .username{m.username()},
        .createdAt{m.createdAt()},
            .updatedAt{m.updatedAt()}
    };
    SetMember(info);

}

void Session::SetMember(const MemberInfo &m)
{
    m_member.reset(new MemberModel);
    m_member->Set(m);
}

// #### SessionFactory

std::unique_ptr<SessionFactory> SessionFactory::factory;

SessionFactory::SessionFactory() = default;

SessionFactory &SessionFactory::Instance()
{
    if(!factory){
        factory.reset(new SessionFactory);
    }
    return *factory;
}

Session &SessionFactory::Current()
{
    if(!m_session){
        m_session.reset(new Session);
    }
    return *m_session;
}
}
