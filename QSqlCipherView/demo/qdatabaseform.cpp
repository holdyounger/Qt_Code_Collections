#include "qdatabaseform.h"
#include "ui_qdatabaseform.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif

#define QSQLCIPHER "qsqlcipher.dll"

QDataBaseForm::QDataBaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDataBaseForm)
{
    ui->setupUi(this);

    Init();

    QIcon icon(":/SQL.ico");
    setWindowIcon(icon);

    QFile f(":/style.qss");

    if (!f.exists())   {
        printf("Unable to set stylesheet, file not found\n");
    }
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        setStyleSheet(ts.readAll());
    }

    QFile fbtn(":/button.qss");

    if (!fbtn.exists())   {
        printf("Unable to set stylesheet, file not found\n");
    }
    else   {
        fbtn.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&fbtn);
        ui->pushBtnOpen->setStyleSheet(ts.readAll());
        ui->pushBtnClear->setStyleSheet(ts.readAll());
    }


}

QDataBaseForm::~QDataBaseForm()
{
    delete ui;
}

void QDataBaseForm::Init()
{
    ui->tabWidget->clear();
    ui->tabWidget->setCurrentIndex(0);

    QLabel *labDefault = new QLabel;
    labDefault->setText(QString("请选择想要打开的数据库"));
    ui->tabWidget->addTab(labDefault,"");
    ui->tabWidget->setTabBarAutoHide(true);
    setWindowTitle("查看数据库");
}

bool QDataBaseForm::openMyDb(QString dbname, QString passWd)
{
    qDebug() << "[START OPEN]--------------------------" << QSqlDatabase::drivers();
    qDebug() << "[START OPEN]--------------------------" << dbname << passWd;
    QSqlDatabase dbconn = QSqlDatabase::addDatabase("SQLITECIPHER", "OPENDB"); // QSQLITE QSQLCIPHER
    dbconn.setDatabaseName(QString(dbname));

    qDebug() << QString("【Encode DB %1】").arg(dbname);
    dbconn.setPassword(passWd);

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
    ui->tabWidget->clear();

    for(int i = 0; i < Tables.count(); i++)
    {
        QTableWidget *table = new QTableWidget;
        QStringList head;
        QString str = QString("PRAGMA table_info( %1 )").arg(Tables[i]);

        {
            queryLoc.prepare(str);
            if (queryLoc.exec())
                while (queryLoc.next())
                    head << queryLoc.value(1).toString();
            else
                QMessageBox::critical(this, QString("Error"), queryLoc.lastError().text(), QMessageBox::Ok);

            table->setColumnCount(head.count());
            table->setHorizontalHeaderLabels(head);
        }

        queryLoc.prepare(QString("select * from %1;").arg(Tables[i]));

        int row = 0;
        if (queryLoc.exec())
        {
            while (queryLoc.next())
            {
                QStringList strItem;

                strItem.clear();

                for (int count = 0; count < head.count(); count++)
                    strItem << queryLoc.value(count).toString();

                table->insertRow(row);
                for (int col = 0; col < strItem.length() && !strItem[col].isEmpty(); col++)
                    table->setItem(row, col, new QTableWidgetItem(strItem[col]));

                row++;
            }
        }
        ui->tabWidget->addTab(table,Tables[i]);
    }

    for(int i = 0; i < Tables.count(); i++)
    {
    }
    m_database.close();
}

void QDataBaseForm::setStatus()
{
    QFileInfo info(m_fileName);
    QString fileName = info.fileName();

    setWindowTitle(fileName);
}

void QDataBaseForm::on_pushBtnOpen_clicked()
{

    if(m_database.isOpen())
    {
        m_database.close();
    }
    m_fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open Database File"), 
        m_filePath.isEmpty() ? QDir::homePath() : m_filePath, 
        tr("Image Files (*.db)"));

	if (m_fileName.isEmpty())
		return;

    m_filePath = QFileInfo(m_fileName).filePath();

    ui->label->setText(m_fileName);

    bool ok;
    m_passWd = QInputDialog::getText(this, tr("请输入密码"),
                                     tr("密码："), QLineEdit::Normal,
                                     "Trust05051025", &ok);

    if(!ok || m_fileName.isEmpty())
        return;

    if( !openMyDb(m_fileName,m_passWd) )
    {
        QMessageBox::warning(this, tr("Error"),
                             tr("密码不对\n"
                                ""),
                             QMessageBox::Ok);
        return;
    }

    setStatus();

    showDatabase();
}


void QDataBaseForm::on_pushBtnClear_clicked()
{
    Init();
}