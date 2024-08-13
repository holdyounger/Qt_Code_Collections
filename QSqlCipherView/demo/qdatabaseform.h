#ifndef QDATABASEFORM_H
#define QDATABASEFORM_H

#include <QWidget>
#include <QString>
#include <QFileDialog>
#include <QInputDialog>
#include <QtSql/QtSql>
#include <QCoreApplication>
#include <QTemporaryDir>
#include <QByteArray>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QTableWidget>
#include <QFileInfo>

namespace Ui {
class QDataBaseForm;
}

class QDataBaseForm : public QWidget
{
    Q_OBJECT


public:
    explicit QDataBaseForm(QWidget *parent = nullptr);
    ~QDataBaseForm();

private:
    void Init();
    bool openMyDb(QString dbname, QString passWd);
    void showDatabase();
    void setStatus();
private slots:
    void on_pushBtnOpen_clicked();

    void on_pushBtnClear_clicked();

private:
    QString m_fileName;
    QString m_passWd;

    QString  m_filePath;

    QSqlDatabase m_database;
private:
    Ui::QDataBaseForm *ui;
};

#endif // QDATABASEFORM_H
