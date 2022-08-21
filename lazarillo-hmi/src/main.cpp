#include <QGuiApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>

#include "lazarillo-hmi/service.h"

#include "utils/style.h"

using lzr::utils::Style;

int main(int argc, char *argv[])
{
    auto service = std::make_shared<utils::ServiceBase>(argc, argv);
    service->run<>("lazarillo-hmi");
}

//     qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

//     QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//     QGuiApplication app(argc, argv);
//     app.setOrganizationName("Adrián Morente");
//     app.setOrganizationDomain("");

//     QTranslator translator;
//     const QStringList uiLanguages = QLocale::system().uiLanguages();
//     for (const QString &locale : uiLanguages)
//     {
//         const QString baseName = "lazarillo-hmi_" + QLocale(locale).name();
//         if (translator.load(":/i18n/" + baseName))
//         {
//             app.installTranslator(&translator);
//             break;
//         }
//     }

//     qmlRegisterUncreatableType<lzr::utils::Style>(
//         "lazarillo.utils", 1, 0, "Style", "Style enum type not creatable.");
//     qRegisterMetaType<const lzr::utils::Style *>("const Style");

//     QQmlApplicationEngine engine;
//     engine.addImportPath(":/");

//     Style style;
//     style.changeSkin();
//     engine.rootContext()->setContextProperty("style", &style);

//     // Finally create QML window
//     const QUrl url(QStringLiteral("qrc:/main.qml"));
//     QObject::connect(
//         &engine, &QQmlApplicationEngine::objectCreated, &app,
//         [url](QObject *obj, const QUrl &objUrl)
//         {
//             if (!obj && url == objUrl)
//                 QCoreApplication::exit(-1);
//         },
//         Qt::QueuedConnection);
//     engine.load(url);

//     return app.exec();
// }
