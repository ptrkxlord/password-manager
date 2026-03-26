#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "domain/VaultManager.h"
#include "domain/EntryService.h"
#include "domain/PasswordGenerator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setOrganizationName("ptkxlord");
    app.setOrganizationDomain("ptkxlord.com");
    app.setApplicationName("ptkxlord");

    VaultManager vaultManager;
    PasswordGenerator pwdGen;

    QQmlApplicationEngine engine;
    
    engine.rootContext()->setContextProperty("vaultManager", &vaultManager);
    engine.rootContext()->setContextProperty("passwordGenerator", &pwdGen);

    const QUrl url(u"qrc:/qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
