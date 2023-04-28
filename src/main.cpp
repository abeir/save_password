// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"
#include "constants.h"
#include "account_manager.h"
#include "member_manager.h"
#include "session.h"
#include "data/data_manager.h"
#include "setting_manager.h"
#include "util/settings.h"


#define QML_COMPONENT_URL "com.abeir.protect"
#define QML_COMPONENT_VERSION_MAJOR 1
#define QML_COMPONENT_VERSION_MINOR 0


#define QML_REGISTER_SINGLETON_OBJECT(clazz, object) \
    qmlRegisterSingletonInstance(QML_COMPONENT_URL, QML_COMPONENT_VERSION_MAJOR, QML_COMPONENT_VERSION_MINOR, #clazz, object)

#define QML_REGISTER_SINGLETON_TYPE(clazz) \
    QScopedPointer<clazz> clazz##__(new clazz); \
    qmlRegisterSingletonInstance(QML_COMPONENT_URL, QML_COMPONENT_VERSION_MAJOR, QML_COMPONENT_VERSION_MINOR, #clazz, clazz##__.get())

#define QML_REGISTER_UNCREATABLE(clazz, reason) \
    qmlRegisterUncreatableType<clazz>(QML_COMPONENT_URL, QML_COMPONENT_VERSION_MAJOR, QML_COMPONENT_VERSION_MINOR, #clazz, reason);


using namespace PROTECT_NAMESPACE;


int main(int argc, char *argv[])
{
    set_qt_environment();

    QML_REGISTER_UNCREATABLE(Session, "session");
    QML_REGISTER_UNCREATABLE(AccountModel, "account model");
    QML_REGISTER_UNCREATABLE(MemberModel, "member model");

    QML_REGISTER_SINGLETON_TYPE(Constants);
    QML_REGISTER_SINGLETON_TYPE(AccountManager);
    QML_REGISTER_SINGLETON_TYPE(MemberManager);

    QScopedPointer<SettingManager> settingManager(new SettingManager);
    QML_REGISTER_SINGLETON_OBJECT(SettingManager, settingManager.get());


    QGuiApplication app(argc, argv);

    DataManager::init(settingManager->Setting(), &app);

    QObject::connect(settingManager.get(), &SettingManager::dataLocationChanged, [](){
        DataManager::reset();
    });

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:Main/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);


    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        DataManager::destroy();
        return -1;
    }

    int ret = app.exec();
    DataManager::destroy();
    return ret;
}
