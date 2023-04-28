
#include "setting_manager.h"

#include <QFileInfo>
#include <QFile>

namespace PROTECT_NAMESPACE {

SettingManager::SettingManager(const QString &file, QObject *parent)
    : QObject{parent}
    , m_settings{new Settings(file)}
{
}


QString SettingManager::dataLocation()
{
    return m_settings->DataLocation();
}

void SettingManager::setDataLocation(const QString &v)
{
    if(v.isEmpty() || v == m_settings->DataLocation()){
        emit setFailed("not a new data location");
        return;
    }
    QString oldUri = m_settings->DatabaseUri();
    m_settings->SetDataLocation(v);
    QString newUri = m_settings->DatabaseUri();
    if(QFileInfo::exists(newUri)){  // 新设置的路径存在数据文件
        emit dataLocationChanged();
        emit setSuccess();
        return;
    }
    if(!copyData(oldUri, newUri)){
        emit setFailed("backup data failed");
        return;
    }
    emit dataLocationChanged();
    emit setSuccess();
}

bool SettingManager::copyData(const QString &old, const QString &new_)
{
    if(old.isEmpty() || !QFileInfo::exists(old)){
        return false;
    }
    return QFile::copy(old, new_);
}

}
