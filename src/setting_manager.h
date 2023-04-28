
#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include "global_defines.h"
#include "util/settings.h"
#include <QObject>
#include <QString>
#include <memory>


namespace PROTECT_NAMESPACE {

class SettingManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString dataLocation READ dataLocation WRITE setDataLocation NOTIFY dataLocationChanged)
public:
    explicit SettingManager(const QString &file = {}, QObject *parent = nullptr);

    QString dataLocation();
    void setDataLocation(const QString &v);

    inline std::shared_ptr<Settings> Setting() { return m_settings; }

signals:
    void setSuccess();
    void setFailed(const QString &msg);

    void dataLocationChanged();

private:
    bool copyData(const QString &old, const QString &new_);

    std::shared_ptr<Settings> m_settings;
};

}
#endif // SETTINGMANAGER_H
