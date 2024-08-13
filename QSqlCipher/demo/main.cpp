#include <QtSql/QtSql>
#include <QApplication >
#include <QTemporaryDir>
#include <QByteArray>
#include "qdatabaseform.h"
//#ifndef QT_DEBUG
//#error Must be built in debug mode!
//#endif

#define Getname(x) (#x)

enum ENUM_SQLKEY {
    QSQLITE_CREATE_KEY = 0,
    QSQLITE_UPDATE_KEY,
    QSQLITE_REMOVE_KEY,
    QSQLITE_BUSY_TIMEOUT = 3,
    QSQLITE_OPEN_READONLY,
    QSQLITE_OPEN_URI,
    QSQLITE_ENABLE_SHARED_CACHE
};

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif

#ifdef Q_OS_IOS
#  include <QtPlugin>

Q_IMPORT_PLUGIN(SqliteCipherDriverPlugin)
#endif

#define CONNECTION_FAILED -1

#define TRUSTAGENT_CONFIG_DATABASE_ENCRY    "TrustConf.db"
#define TRUSTAGENT_CONFIG_DATABASE          "TrustAgent.db"

QSqlDatabase openMyDb(const char *dbname, const char *passWd);

// 拷贝数据库文件到 TrustConf.db
bool copyFiletoNew(QString srcPath, QString dstPath, bool coverFileIfExist)
{
    if (srcPath == dstPath) {
        return true;
    }

    if (!QFile::exists(srcPath)) {
        return false;
    }

    if (QFile::exists(dstPath)) {
        if (coverFileIfExist) {
            QFile::remove(dstPath);
        }
    }

    if (!QFile::copy(srcPath, dstPath)) {
        return false;
    }
    return true;
}

QSqlDatabase openMyDb(const char *dbname, const char *passWd)
{
    qDebug() << "[START OPEN]--------------------------";
    QSqlDatabase dbconn = QSqlDatabase::addDatabase("SQLITECIPHER", "OPENDB"); // QSQLITE QSQLCIPHER SQLITECIPHER
    dbconn.setDatabaseName(QString(dbname));

    qDebug() << QString("【Encode DB %1】").arg(dbname);
    dbconn.setPassword(passWd);
    //dbconn.setConnectOptions("QSQLITE_UPDATE_KEY=test");
    //dbconn.setConnectOptions("QSQLITE_REMOVE_KEY");
    //dbconn.setConnectOptions(QString("%1=%2").arg(Getname(QSQLITE_UPDATE_KEY)).arg("newtest"));

    bool open = dbconn.open();
    qDebug() << "[opt" << QString(dbname) << "DB] open: " << open;
    qDebug() << "[opt" << QString(dbname) << "DB] isOpen(): " << dbconn.isOpen() << dbconn.isOpenError();
    qDebug() << "[opt" << QString(dbname) << "DB] create_key: " << dbconn.lastError();
    qDebug() << "[opt" << QString(dbname) << "DB] Database:" << dbconn;
    qDebug() << "[opt" << QString(dbname) << "DB] Database:" << dbconn.connectOptions().contains("QSQLITE_REMOVE_KEY");
    qDebug() << "[END OPEN]--------------------------";


    if (!dbconn.isOpen())
    {
        qDebug() << "Connection failed: " << dbconn.lastError().driverText();
        exit(CONNECTION_FAILED);
    }

    dbconn.close();
    dbconn.open();

    return dbconn;
}

QSqlDatabase optMyDB(const char *dbname)
{
    qDebug() << "[START]--------------------------";
    QSqlDatabase dbconn = QSqlDatabase::addDatabase("QSQLCIPHER", dbname); // QSQLITE QSQLCIPHER
    QString dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    dbconn.setDatabaseName(QString(dbname));
    // 加密
    if(QString(dbname) == QString("local"))
    {
        copyFiletoNew(dir + "/" + QString(dbname) + ".db",dir + "/copyFirst.db",1);
        // QFile::remove(dir + "/copyFirst.db");

        qDebug() << QString("【Encode DB %1】").arg(dbname);
        dbconn.setPassword("newtest");
        dbconn.setConnectOptions("QSQLITE_UPDATE_KEY=test");
        dbconn.setConnectOptions("QSQLITE_REMOVE_KEY");
        //dbconn.setConnectOptions(QString("%1=%2").arg(Getname(QSQLITE_UPDATE_KEY)).arg("newtest"));
    }

    bool open = dbconn.open();
    qDebug() << "[opt" << QString(dbname) << "DB] open: " << open;
    qDebug() << "[opt" << QString(dbname) << "DB] isOpen(): " << dbconn.isOpen() << dbconn.isOpenError();
    qDebug() << "[opt" << QString(dbname) << "DB] create_key: " << dbconn.lastError();
    qDebug() << "[opt" << QString(dbname) << "DB] Database:" << dbconn;
    qDebug() << "[opt" << QString(dbname) << "DB] Database:" << dbconn.connectOptions().contains("QSQLITE_REMOVE_KEY");
    qDebug() << "[END]--------------------------";


    if (!dbconn.isOpen())
    {
        qDebug() << "Connection failed: " << dbconn.lastError().driverText();
        exit(CONNECTION_FAILED);
    }

    return dbconn;
}

void testOPT()
{
    QSqlDatabase dbLocal = optMyDB("local");
    auto dbCIPHER = optMyDB("QSQLCIPHER");

    QSqlQuery queryLoc(dbLocal);
    QSqlQuery queryCip(dbCIPHER);

    queryCip.exec("create table IF NOT EXISTS test(Addr VARCHAR(255) NOT NULL, AuthType VARCHAR(255) NOT NULL, Account VARCHAR(255) NOT NULL, Password VARCHAR(255) NOT NULL"
                  ")");

    qDebug() << endl << "START QURTY"<< endl;
    queryLoc.exec("select * from dbAccount;");
    while (queryLoc.next()) {
        qDebug() << queryLoc.value(0).toString() << ": "
                 << queryLoc.value(1).toString() << ": "
                 << queryLoc.value(2).toString() << ": "
                 << queryLoc.value(3).toString();

    }


    qDebug() << "Encode Query";
    queryCip.exec("select * from test;");
    while (queryCip.next()) {
        qDebug() << queryCip.value(0).toString() << ": "
                 << queryCip.value(1).toString() << ": "
                 << queryCip.value(2).toString() << ": "
                 << queryCip.value(3).toString();

        /* 保存到新的数据库 */
        //        QString strInsert = QString("insert into test values('%1', '%2', '%3', '%4');").arg(queryLoc.value(0).toString())
        //                .arg(queryLoc.value(1).toString())
        //                .arg(queryLoc.value(2).toString())
        //                .arg(queryLoc.value(3).toString());
        //        queryCip.exec(strInsert);

    }


    qDebug() << __LINE__ << dbLocal.tables();

    dbLocal.close();
    dbCIPHER.close();

}

void testOPEN()
{
    QString strPath = QString("%1/Trustagent/%2").arg(QDir::homePath()).arg("TrustConf.db");
    auto dbconn = openMyDb(strPath.toStdString().c_str(),"Trust05051025"); //

    qDebug() << "[TABLES]" << dbconn.tables();


    QSqlQuery queryLoc(dbconn);
    QStringList Tables = dbconn.tables();

    qDebug() << endl << "START QURTY"<< endl;
    for(int i = 0; i < Tables.count(); i++)
    {
        qDebug() << "QUERY" << Tables[i];
        queryLoc.exec(QString("select * from %1;").arg(Tables[i]));
        while (queryLoc.next()) {
            qDebug() << queryLoc.value(0).toString() << ": "
                     << queryLoc.value(1).toString() << ": "
                     << queryLoc.value(2).toString() << ": "
                     << queryLoc.value(3).toString();

        }
    }

    dbconn.close();



}

QByteArray changeBa(QByteArray ba)
{
    ba.replace("1","2");
    return ba;
}

int main(int argc, char *argv[])
{
    QApplication  app(argc, argv);
    // Q_UNUSED(app)

    // qDebug() << QSqlDatabase::drivers();

   // testOPEN();

    QDataBaseForm dataForm;
    dataForm.show();


//    QByteArray ba("123123123123");
//    qDebug() << changeBa(ba);
//    qDebug() << ba;

    // system("pause");
    return app.exec();
}
