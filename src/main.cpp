#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QLocale>
#include <QTranslator>

#include <boost/numeric/odeint.hpp>

#include "floor.h"
#include "ball.h"
#include "stellarengine.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Stellarlink_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;

    QPointer<Ball> ballLogik = new Ball(25);
    QPointer<StellarEngine> stellarEngine = new StellarEngine();
    QPointer<Floor> floorLogik = new Floor();

    engine.rootContext() -> setContextProperty("ballLogik", ballLogik);
    engine.rootContext() -> setContextProperty("stellarEngine", stellarEngine);
    engine.rootContext() -> setContextProperty("floorLogik", floorLogik);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
