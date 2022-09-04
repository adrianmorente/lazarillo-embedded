#include "lazarillo-hmi/service.h"

#include "lazarillo-hmi/utils/style.h"
#include "message_receivers/event_reboot_receiver.h"

#include "topics/topics.h"

#include <QLocale>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>

using lzr::hmi::Service;
using lzr::utils::Style;
using namespace messages::topics;

Service::Service(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    m_app = new QGuiApplication(argc, argv);
    m_app->setOrganizationName("Adrián Morente");
    m_app->setOrganizationDomain("");

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "lazarillo-hmi_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            m_app->installTranslator(&translator);
            break;
        }
    }

    qmlRegisterUncreatableType<Style>("lazarillo.utils", 1, 0, "Style",
                                      "Style enum type not creatable.");
    qRegisterMetaType<const Style *>("const Style");
}

Service::~Service()
{
    delete m_app;
}

std::string Service::get_name()
{
    return "lazarillo-hmi";
}

void Service::init()
{
    auto event_reboot_receiver =
        std::make_shared<lzr::hmi::EventRebootReceiver>();
    subscribe(WEB_GATEWAY_EVENT_TOPIC, messages::EventReboot::NAME,
              event_reboot_receiver);
}

int Service::run_internal()
{
    QQmlApplicationEngine engine;
    engine.addImportPath(":/");

    Style style;
    style.changeSkin();
    engine.rootContext()->setContextProperty("style", &style);

    // Finally create QML window
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, m_app,
        [url](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return m_app->exec();
}

void Service::finish() {}
