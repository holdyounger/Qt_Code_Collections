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

#define TRUSTAGENT_CONFIG_DATABASE_ENCRY    "Trustconf.db"
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

    QSqlDatabase dbconn1;
    QSqlDatabase dbconn;

    {
        qDebug() << "[1~~~]--------------------------";

        if (QSqlDatabase::contains("qt_sql_default_connection_1"))
        {
            dbconn1 = QSqlDatabase::database("qt_sql_default_connection_1");
        }
        else
        {
            dbconn1 = QSqlDatabase::addDatabase("QSQLITE","qt_sql_default_connection_1"); // QSQLITE QSQLCIPHER SQLITECIPHER
        }

        dbconn1.setDatabaseName(QString("C:/Users/shimingming/Trustagent/TrustAgent1.db"));

        bool open = dbconn1.open();
        qDebug() << "[opt" << dbconn1.connectionName() << "DB] open: " << open;
        qDebug() << "[opt" << dbconn1.connectionName() << "DB] isOpen(): " << dbconn1.isOpen() << dbconn1.isOpenError();
        qDebug() << "[opt" << dbconn1.connectionName() << "DB] create_key: " << dbconn1.lastError();
        qDebug() << "[opt" << dbconn1.connectionName() << "DB] Database:" << dbconn1.database();
        if (!dbconn1.isOpen())
        {
            qDebug() << "Connection failed: " << dbconn1.lastError().driverText();
        }

        // 查询
        QSqlQuery queryLoc(dbconn1);
        QStringList Tables = dbconn1.tables();

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

        dbconn1.close();

        qDebug() << "[1~~~]--------------------------\n\n\n\n\n\n";

    }

    {

        if (QSqlDatabase::contains("qt_sql_default_connection_2"))
        {
            dbconn = QSqlDatabase::database("qt_sql_default_connection_2");
        }
        else
        {
            dbconn = QSqlDatabase::addDatabase("QSQLCIPHER","qt_sql_default_connection_2"); // QSQLITE QSQLCIPHER SQLITECIPHER
        }

        dbconn.setDatabaseName(QString("C:/Users/shimingming/Trustagent/TrustConf.db"));

        qDebug() << "[2~~~]--------------------------";
        qDebug() << QString("【Encode DB %1】").arg(dbname);
        dbconn.setPassword(passWd);

        bool open = dbconn.open();
        qDebug() << "[opt" << dbconn.connectionName() << "DB] open: " << open;
        qDebug() << "[opt" << dbconn.connectionName() << "DB] isOpen(): " << dbconn.isOpen() << dbconn.isOpenError();
        qDebug() << "[opt" << dbconn.connectionName() << "DB] create_key: " << dbconn.lastError();
        qDebug() << "[opt" << dbconn.connectionName() << "DB] Database:" << dbconn.database();
        if (!dbconn.isOpen())
        {
            qDebug() << "Connection failed: " << dbconn.lastError().driverText();
        }

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

        qDebug() <<"[2~~~]--------------------------";
    }

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
    qDebug() << "[opt" << QString(dbname) << "DB] Database:" << dbconn.databaseName();
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

    return ;
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

void testCopyFile()
{
    QString dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    copyFiletoNew("C:/Users/shimingming/TrustAgent/TrustAgent.db", "C:/Users/shimingming/TrustAgent/TrustAgent111.db",1);
}

int main(int argc, char *argv[])
{
    QApplication  app(argc, argv);
    // Q_UNUSED(app)
    // testCopyFile();
    //qDebug() << QSqlDatabase::drivers();
    // return 0;
    //testOPEN();
    //return 0;
    QDataBaseForm dataForm;
    dataForm.show();


    //    QByteArray ba("123123123123");
    //    qDebug() << changeBa(ba);
    //    qDebug() << ba;

    // system("pause");
    return app.exec();
}
