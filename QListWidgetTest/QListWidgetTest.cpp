#include "QListWidgetTest.h"

QListWidgetTest::QListWidgetTest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	QPixmap pixmap("D:\\CodeSource\\C++\\vs2019\\QListWidgetTest\\Win11.png");

	ui.label->setFixedSize(400,250);
	ui.label->setPixmap(pixmap);

	// ui.label->setText(QString("�����ı�"));

	initListWidget();
}

void QListWidgetTest::initListWidget()
{
	ui.listWidget->setCurrentRow(2);

	QStringList StrListHeader;
	StrListHeader << QString("ѡ��") << QString("���") << QString("�ļ���");
	new QListWidgetItem(tr("�����ԡ�QListWidget���QListWidgetItem"), ui.listWidget);

	// ���� List ����ʾ��ʽ
	ui.listWidget->setViewMode(QListWidget::ListMode);

	QListWidgetItem* ListItem = new QListWidgetItem;
	//    ListItem->setText();

	QListWidgetItem* WContainerItem = new QListWidgetItem(ui.listWidget);
	QWidget* WContainer = new QWidget(ui.listWidget); //�½�һ��QWidget����
	QGridLayout* Glayout = new QGridLayout;

	/*************start*****************/
	/* �����������Ҫ�Ŀؼ� */
	// ����ı��༭��
	QLineEdit* lineEdit = new QLineEdit;
	Glayout->addWidget(lineEdit, 1, 0);
	
	// ��ӹ��߰�ť
	QToolButton* toolButton = new QToolButton;
	Glayout->addWidget(toolButton, 2, 0);

	// ��ӵ�ѡ��ť
	QRadioButton* radioButton_1 = new QRadioButton;
	Glayout->addWidget(radioButton_1, 3, 0);

	WContainer->setLayout(Glayout);
	WContainer->setMinimumHeight(50);
	/******************end****************/

	// ���һ��Label
	/*************start*****************/
	QWidget* WContainer_1 = new QWidget(ui.listWidget); //�½�һ��QWidget����
	QListWidgetItem* labelContainer = new QListWidgetItem(ui.listWidget);
	QGridLayout* GLayout_1 = new QGridLayout;
	QLabel* label = new QLabel;
	QPixmap pixmap("D:\\CodeSource\\C++\\vs2019\\QListWidgetTest\\Win11.png");
	label->setPixmap(pixmap);
	label->setStyleSheet("QLabel{"
		"background-image:url(D:\\CodeSource\\C++\\vs2019\\QListWidgetTest\\Win11.png);"
		"background-position:top right;"
		"background-origin:content;"
		"background-repeat:none;"
		"}");
	GLayout_1->addWidget(label, 0, 0);
	WContainer_1->setLayout(GLayout_1);
	ui.listWidget->setItemWidget(labelContainer, WContainer_1);
	/******************end****************/

	Glayout->addWidget(label, 3, 0);

	WContainerItem->setSizeHint(QSize(40, 40));
	ui.listWidget->setItemWidget(WContainerItem, WContainer);//��WContainer����WContainerItem
}
