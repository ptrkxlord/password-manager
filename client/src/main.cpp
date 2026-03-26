#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "domain/VaultManager.h"
#include "domain/EntryService.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setOrganizationName("ptkxlord");
    app.setOrganizationDomain("ptkxlord.com");
    app.setApplicationName("ptkxlord");

    VaultManager vaultManager;
    EntryService entryService(nullptr); // Initialized with nullptr, will be set when vault opens? 
    // Wait, EntryService needs a db manager. Better to pass the db manager from VaultManager.

    QQmlApplicationEngine engine;
    
    qmlRegisterType<VaultManager>("com.ptkxlord.security", 1, 0, "VaultManager");
    // Or just set context properties
    engine.rootContext()->setContextProperty("vaultManager", &vaultManager);

    const QUrl url(u"qrc:/qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
