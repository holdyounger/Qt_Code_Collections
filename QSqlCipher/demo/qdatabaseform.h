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
#include <QTreeWidgetItem>
#include <QTreeWidget>

namespace Ui {
class QDataBaseForm;
}

class QDataBaseForm : public QWidget
{
    Q_OBJECT

    void Init();
public:
    explicit QDataBaseForm(QWidget *parent = nullptr);
    ~QDataBaseForm();

    bool openMyDb(QString dbname, QString passWd);
    void showDatabase();
private slots:
    void on_pushButton_clicked();

private:
    QString m_fileName;
    QString m_passWd;

    QSqlDatabase m_database;
private:
    Ui::QDataBaseForm *ui;
};

#endif // QDATABASEFORM_H
