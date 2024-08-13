/********************************************************************************
** Form generated from reading UI file 'qdatabaseform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QDATABASEFORM_H
#define UI_QDATABASEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QDataBaseForm
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushBtnOpen;
    QPushButton *pushBtnClear;
    QSpacerItem *horizontalSpacer;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;

    void setupUi(QWidget *QDataBaseForm)
    {
        if (QDataBaseForm->objectName().isEmpty())
            QDataBaseForm->setObjectName(QStringLiteral("QDataBaseForm"));
        QDataBaseForm->resize(743, 427);
        gridLayout = new QGridLayout(QDataBaseForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushBtnOpen = new QPushButton(QDataBaseForm);
        pushBtnOpen->setObjectName(QStringLiteral("pushBtnOpen"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushBtnOpen->sizePolicy().hasHeightForWidth());
        pushBtnOpen->setSizePolicy(sizePolicy);
        pushBtnOpen->setMinimumSize(QSize(60, 0));

        horizontalLayout->addWidget(pushBtnOpen);

        pushBtnClear = new QPushButton(QDataBaseForm);
        pushBtnClear->setObjectName(QStringLiteral("pushBtnClear"));
        sizePolicy.setHeightForWidth(pushBtnClear->sizePolicy().hasHeightForWidth());
        pushBtnClear->setSizePolicy(sizePolicy);
        pushBtnClear->setMinimumSize(QSize(60, 0));

        horizontalLayout->addWidget(pushBtnClear);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(QDataBaseForm);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);

        label = new QLabel(QDataBaseForm);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 30);
        verticalLayout->setStretch(2, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(QDataBaseForm);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QDataBaseForm);
    } // setupUi

    void retranslateUi(QWidget *QDataBaseForm)
    {
        QDataBaseForm->setWindowTitle(QApplication::translate("QDataBaseForm", "Form", Q_NULLPTR));
        pushBtnOpen->setText(QApplication::translate("QDataBaseForm", "\351\200\211\346\213\251\346\226\207\344\273\266", Q_NULLPTR));
        pushBtnClear->setText(QApplication::translate("QDataBaseForm", "\346\270\205\347\251\272", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QDataBaseForm", "Tab 1", Q_NULLPTR));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QDataBaseForm: public Ui_QDataBaseForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QDATABASEFORM_H
