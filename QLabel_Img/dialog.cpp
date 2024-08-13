#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
   // setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint | Qt::Window);
    //setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("#Dialog{"
                  "border-image: url(:/bgimg_334.png);"
                  "background-position: center;"
                  "backgroun d-repeat: no-repeat;"
                  "}");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::finish(QWidget* mainWin)
{
    if (mainWin) {
        if (!mainWin->windowHandle())
            mainWin->createWinId();
    //	QTest::qWaitForWindowExposed(mainWin->windowHandle());
    }
    close();
}
