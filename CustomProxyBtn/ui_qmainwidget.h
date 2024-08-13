/********************************************************************************
** Form generated from reading UI file 'qmainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMAINWIDGET_H
#define UI_QMAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QMainWidget
{
public:
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QGraphicsView *graphicsView;
    QFrame *frame_3;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_5;

    void setupUi(QWidget *QMainWidget)
    {
        if (QMainWidget->objectName().isEmpty())
            QMainWidget->setObjectName(QStringLiteral("QMainWidget"));
        QMainWidget->resize(574, 456);
        frame = new QFrame(QMainWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(70, 250, 201, 131));
        frame->setLayoutDirection(Qt::LeftToRight);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        frame_2 = new QFrame(QMainWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(280, 80, 251, 181));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        graphicsView = new QGraphicsView(frame_2);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMinimumSize(QSize(0, 0));
        graphicsView->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(graphicsView, 0, 0, 1, 1);

        frame_3 = new QFrame(QMainWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(40, 40, 201, 131));
        frame_3->setLayoutDirection(Qt::LeftToRight);
        frame_3->setStyleSheet(QStringLiteral("background-color: rgb(0, 170, 0);"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_3);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));

        gridLayout_4->addLayout(gridLayout_5, 0, 0, 1, 1);


        retranslateUi(QMainWidget);

        QMetaObject::connectSlotsByName(QMainWidget);
    } // setupUi

    void retranslateUi(QWidget *QMainWidget)
    {
        QMainWidget->setWindowTitle(QApplication::translate("QMainWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QMainWidget: public Ui_QMainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMAINWIDGET_H
