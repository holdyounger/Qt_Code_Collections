#include "qeventtest.h"
#include "ui_qeventtest.h"

QEventTest::QEventTest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QEventTest)
{
    ui->setupUi(this);
}


QEventTest::~QEventTest()
{
    delete ui;
}

void QEventTest::test_Block()
{
   Log() << endl;

    QEventLoop ev;

    connect(this, SIGNAL(myfinished()), &ev, SLOT(quit()));
    ev.exec(QEventLoop::ExcludeUserInputEvents);
    Log() << ev.isRunning() << endl;
    // ev.exec();
    Log() << ev.isRunning() << endl;

    if(!m_success){
        QMessageBox::warning(this, "Update Error", QString(tr("测试数据上传失败，错误信息: %1, 错误码: %2")).arg("自定义").arg("阻塞测试"), QMessageBox::Ok);
        ui->lblMessage->setText(tr("当前产品条码作业未完成"));

    }
    else{
         ui->lblMessage->setText(tr("当前产品条码作业完成"));
    }
    Log() << ev.isRunning() << endl;
}


void QEventTest::on_pushButton_clicked()
{

    //上面代码阻塞程序，知道接收到信号finished才结束时，执行下面的代码
    emit myfinished();

    m_success = true;
    QTimer::singleShot(3 * 1000, this,[=](){
        emit myfinished();
        Log() << endl;
    });
    test_Block();


}

