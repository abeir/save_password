
#include "settings.h"
#include <QDir>
#include <QFileInfo>
#include <QVariant>
#include <QDebug>


#define PROTECT_SETTINGS_DIR ".protect"
#define PROTECT_SETTINGS_FILENAME "protect.ini"
#define PROTECT_SETTINGS_DB_FILENAME "protect.data"

#define PROTECT_SETTINGS_KEY_DATALOCATION "data_location"


namespace PROTECT_NAMESPACE {

Settings::Settings(const QString &file)
{
    load(file);
}



QString Settings::iniFileCurrent()
{
    return QDir::current().absoluteFilePath(PROTECT_SETTINGS_FILENAME);
}

QString Settings::iniFileHome()
{
    QString homeDirPath = home();
    return QDir(homeDirPath).absoluteFilePath(PROTECT_SETTINGS_FILENAME);
}

QString Settings::home()
{
    QString homeDirPath = QDir::home().absoluteFilePath(PROTECT_SETTINGS_DIR);
    QDir homeDir(homeDirPath);
    if(!homeDir.exists()){
        homeDir.mkpath(homeDirPath);
    }
    return homeDirPath;
}


QString Settings::DataLocation()
{
    QString dir = m_settings->value(PROTECT_SETTINGS_KEY_DATALOCATION).toString();
    if(!dir.isEmpty() && QDir(dir).exists()){
        return dir;
    }
    return home();
}

void Settings::SetDataLocation(const QString &location)
{
    QString dirPath;
#ifdef Q_OS_WIN
    dirPath = location.mid(8);
#else
    dirPath = location.mid(7);
#endif

    QDir dir(dirPath);
    if(!dir.exists()){
        dir.mkpath(dirPath);
    }
    m_settings->setValue(PROTECT_SETTINGS_KEY_DATALOCATION, dirPath);
    m_settings->sync();
}

QString Settings::DatabaseUri()
{
    QString dir = DataLocation();
    return QDir(dir).absoluteFilePath(PROTECT_SETTINGS_DB_FILENAME);
}

void Settings::load(const QString &file)
{
    std::unique_ptr<QSettings> currentSettings;
    QString current = iniFileCurrent();
    if(QFileInfo::exists(current)){
        currentSettings.reset(new QSettings(current, QSettings::IniFormat));
    }
    std::unique_ptr<QSettings> homeSettings;
    QString home = iniFileHome();
    if(QFileInfo::exists(home)){
        homeSettings.reset(new QSettings(home, QSettings::IniFormat));
    }
    std::unique_ptr<QSettings> specificSettings;
    if(!file.isEmpty() && QFileInfo::exists(file)){
        specificSettings.reset(new QSettings(file, QSettings::IniFormat));
    }

    m_settings.reset(new QSettings(home, QSettings::IniFormat));
    if(currentSettings){
        for(auto &key : currentSettings->allKeys()){
            m_settings->setValue(key, currentSettings->value(key));
        }
    }
    if(homeSettings){
        for(auto &key : homeSettings->allKeys()){
            m_settings->setValue(key, homeSettings->value(key));
        }
    }
    if(specificSettings){
        for(auto &key : specificSettings->allKeys()){
            m_settings->setValue(key, specificSettings->value(key));
        }
    }

    qDebug() << "setting file:" << m_settings->fileName();
}


}
