#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "domain/VaultManager.h"
#include "domain/EntryService.h"
#include "domain/PasswordGenerator.h"
#include "network/ApiClient.h"
#include "network/AuthCallbackServer.h"
#include "domain/ClipboardManager.h"

#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Basic");
    QGuiApplication app(argc, argv);
    
    AuthCallbackServer authServer;

    app.setOrganizationName("ptkxlord");
    app.setOrganizationDomain("ptkxlord.com");
    app.setApplicationName("ptkxlord");

    VaultManager vaultManager;
    PasswordGenerator pwdGen;
    ApiClient apiClient;
    ClipboardManager clipboardManager;

    QQmlApplicationEngine engine;
    
    engine.rootContext()->setContextProperty("vaultManager", &vaultManager);
    engine.rootContext()->setContextProperty("passwordGenerator", &pwdGen);
    engine.rootContext()->setContextProperty("apiClient", &apiClient);
    engine.rootContext()->setContextProperty("clipboard", &clipboardManager);
    engine.rootContext()->setContextProperty("authServer", &authServer);

    const QUrl url(u"qrc:/ptkxlord/src/qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
