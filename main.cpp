#include <QApplication>
#include "mainwindow.h"
#include <QSslSocket>
#include <QNetworkAccessManager>

#include "ganalytics/ganalytics.h"
#include <QUuid>


#define GA_MEASUREMENT_ID "G-NVBDTHHBJC"            // "YOUR_MEASUREMENT_ID"
#define GA_API_SECRET     "2xv8KuzHRNWO68DT6_VCDQ"  // "YOUR_API_SECRET"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // 查詢Qt支持的版本
    bool bSupp = QSslSocket::supportsSsl();
    QString buildVersion = QSslSocket::sslLibraryBuildVersionString();
    QString version = QSslSocket::sslLibraryVersionString();
    qDebug() << bSupp << buildVersion << version;

    // 查看当前网络请求支持协议
    QNetworkAccessManager *accessManager = new QNetworkAccessManager();
    qDebug() << accessManager->supportedSchemes();


    // Init GA
    QString clientID; // You can read ClientID from config
    if (clientID.isEmpty()) {
        clientID = QUuid::createUuid().toString();
        // You can save ClientID from config
    }
    ga->setClientID(clientID);
    ga->setMeasurementId(GA_MEASUREMENT_ID);
    ga->setApiSecret(GA_API_SECRET);
    ga->enable(true);
    ga->setSendInterval(3000);
    ga->setLogLevel(GAnalytics::Debug);

    // Now you can send event by name.
    ga->sendEvent("eventName");

    // Or
    ga->sendEvent("cateGory", "eventName", "eventParamName", "eventParamValue");

    MainWindow w;
    w.show();

    return a.exec();
}
