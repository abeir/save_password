
#ifndef SETTINGS_H
#define SETTINGS_H

#include "global_defines.h"
#include <QString>
#include <QSettings>
#include <memory>


namespace PROTECT_NAMESPACE {


class Settings
{
public:
    explicit Settings(const QString &file = {});

    // is dir
    QString DataLocation();
    void SetDataLocation(const QString &);

    QString DatabaseUri();
private:
    Q_DISABLE_COPY(Settings)

    /**
     * @brief load 加载顺序：current -> home -> specific
     * @param file 特定的配置文件路径 (specific)
     */
    void load(const QString &file);
    QString iniFileCurrent();
    QString iniFileHome();
    QString home();

    std::unique_ptr<QSettings> m_settings;
};

}
#endif // SETTINGS_H
