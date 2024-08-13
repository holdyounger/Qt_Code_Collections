#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    testQByteArray();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::testQByteArray()
{


    QByteArray ba("Hello");

    for(int i = 0; i < ba.length(); i++)
    {
        ba[i] = ba[i] + 5;
    }

    QString nameStr = QVariant("你好").toString();

    this->ui->textEdit->setText( nameStr );
}


void Widget::on_pushButton_clicked()
{
    QString inputStr = this->ui->textEdit->toPlainText();

    QByteArray ba = inputStr.toUtf8();

    for ( int i = 0; i < ba.length(); i++ )
    {
        ba[i] = ba[i] + 1;
    }

    this->ui->textEdit->setText(ba);
}


void Widget::on_pushButton_2_clicked()
{
    QString inputStr = this->ui->textEdit->toPlainText();

    QByteArray ba = inputStr.toUtf8();

    for ( int i = 0; i < ba.length(); i++ )
    {
        ba[i] = ba[i] - 1;
    }

    this->ui->textEdit->setText(ba);
}

