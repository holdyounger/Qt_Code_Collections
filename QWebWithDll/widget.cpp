#include "widget.h"
#include "ui_widget.h"
#include <QLibrary>
#include <QUrl>
#include <QDebug>


static QLibrary myLib("QTrustWebView");

typedef void (*LoadStartedFunc)();
typedef void (*LoadProgressFunc)(int);
typedef void (*LoadFinishedFunc)(bool);
typedef void (*UrlChangedFunc)(const QUrl&);


void Widget::slotLoadStarted()
{
	qDebug() << __FUNCTION__ << __LINE__;
}

void Widget::slotLoadProgress(int progress)
{
	qDebug() << __FUNCTION__ << __LINE__ << progress;
}

void Widget::slotLoadFinished(bool bok)
{
	qDebug() << __FUNCTION__ << __LINE__ << bok;
}

void Widget::slotUrlChanged(const QUrl& url)
{
	qDebug() << __FUNCTION__ << __LINE__ << url;
}


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    using InterFace = void (*)(const QUrl& url);

    InterFace myFunction = (InterFace) myLib.resolve("SetUrl");

    myFunction(QUrl::fromUserInput(ui->lineEdit->text().trimmed()));
}

typedef std::function<void()> FunLoadStartedFunc;
typedef std::function<void(int)> FunLoadProgressFunc;
typedef std::function<void(bool)> FunLoadFinishedFunc;
typedef std::function<void(const QUrl&)> FunUrlChangedFunc;

void Widget::on_pushButton_2_clicked()
{
    qDebug() << myLib.fileName();

    if (myLib.isLoaded())
    {
        return;
	}
    else
    {
        myLib.load();
    }
	qDebug() << myLib.fileName();
	using InterFaceInst = QWidget * (*)();

	using BindLoadStarted = void (*)(FunLoadStartedFunc);
	using BindLoadProgress = void (*)(FunLoadProgressFunc);
	using BindLoadFinished = void (*)(FunLoadFinishedFunc);
	using BindUrlChanged = void (*)(FunUrlChangedFunc);

	FunLoadStartedFunc funLoadStart = std::bind(&Widget::slotLoadStarted);
	FunLoadProgressFunc funLoadProgress = std::bind(&Widget::slotLoadProgress, std::placeholders::_1);
	FunLoadFinishedFunc funLoadFinished = std::bind(&Widget::slotLoadFinished, std::placeholders::_1);
	FunUrlChangedFunc funUrlChanged = std::bind(&Widget::slotUrlChanged, std::placeholders::_1);

	BindLoadStarted InstStart = (BindLoadStarted)myLib.resolve("BindLoadStarted");
	BindLoadProgress InstProgress = (BindLoadProgress)myLib.resolve("BindLoadProgress");
	BindLoadFinished InstFinished = (BindLoadFinished)myLib.resolve("BindLoadFinished");
	BindUrlChanged InstUrlChange = (BindUrlChanged)myLib.resolve("BindUrlChanged");


	InstStart(funLoadStart);
	InstProgress(funLoadProgress);
	InstFinished(funLoadFinished);
    InstUrlChange(funUrlChanged);

	InterFaceInst Inst = (InterFaceInst)myLib.resolve("GetInstance");

	QWidget* widget = Inst();



    if(Inst){}
        ui->grid->addWidget(widget);
}
