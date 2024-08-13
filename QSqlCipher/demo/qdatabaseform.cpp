#include "qdatabaseform.h"
#include "ui_qdatabaseform.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif


QDataBaseForm::QDataBaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDataBaseForm)
{
    ui->setupUi(this);

    Init();
    setWindowTitle("查看数据库");
    QIcon icon(":/SQL.ico");
    setWindowIcon(icon);
    this->show();
}

QDataBaseForm::~QDataBaseForm()
{
    delete ui;
}

void QDataBaseForm::Init()
{
    // ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // 测试

    QStringList headers;
    headers << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8";
    ui->treeWidget->setHeaderLabels(headers);
}

bool QDataBaseForm::openMyDb(QString dbname, QString passWd)
{
    qDebug() << "[START OPEN]--------------------------" << dbname << passWd;
    QSqlDatabase dbconn = QSqlDatabase::addDatabase("QSQLCIPHER", "OPENDB"); // QSQLITE QSQLCIPHER
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

    if (!dbconn.isOpen())
    {
        qDebug() << "Connection failed: " << dbconn.lastError().driverText();
        return false;
    }
    qDebug() << "[END OPEN]--------------------------";
    m_database = dbconn;
    return true;
}

void QDataBaseForm::showDatabase()
{
    QSqlQuery queryLoc(m_database);
    QStringList Tables = m_database.tables();

    qDebug() << endl << "START QURTY"<< endl;
    for(int i = 0; i < Tables.count(); i++)
    {

        // 设置表头
        QStringList head;
        QString str = QString("PRAGMA table_info( %1 )").arg(Tables[i]);

        queryLoc.prepare(str);
        if (queryLoc.exec())
            while (queryLoc.next())
            {
                qDebug() << QString(QString("字段数:%1 字段名:%2 字段类型:%3")).arg(queryLoc.value(0).toString()).arg(queryLoc.value(1).toString()).arg(queryLoc.value(2).toString());
                head << queryLoc.value(1).toString();
            }
        else
            qDebug() << queryLoc.lastError();

        qDebug() << "QUERY" << Tables[i];
        QTreeWidgetItem *root = new QTreeWidgetItem(ui->treeWidget, QStringList(Tables[i]));
        queryLoc.exec(QString("select * from %1;").arg(Tables[i]));
        new QTreeWidgetItem(root, head);
        QStringList strItem;
        while (queryLoc.next()) {
            strItem << queryLoc.value(0).toString()
                    << queryLoc.value(1).toString()
                    << queryLoc.value(2).toString()
                    << queryLoc.value(3).toString();
            new QTreeWidgetItem(root, strItem);
            // items[i]->setBackground(0,Qt::Dense7Pattern);
        }
    }

    m_database.close();
}

void QDataBaseForm::on_pushButton_clicked()
{

    if(m_database.isOpen())
    {
        m_database.close();
    }
    m_fileName = QFileDialog::getOpenFileName(this,
                                              tr("Open Database File"), QDir::homePath(), tr("Image Files (*.db)"));

    ui->lineEdit->setText(m_fileName);

    bool ok;
    m_passWd = QInputDialog::getText(this, tr("请输入密码"),
                                     tr("密码："), QLineEdit::Normal,
                                     "Trust05051025", &ok);
    if (ok && m_passWd.isEmpty())
    {
        qDebug() << "密码为空" << endl;
    }

    if( !openMyDb(m_fileName,m_passWd) )
    {
        QMessageBox::warning(this, tr("Error"),
                             tr("密码不对\n"
                                ""),
                             QMessageBox::Ok);
        return;
    }

    showDatabase();
}

