#-------------------------------------------------
#名称: 认证对话框模块
#作者: VoX
#时间: 2021-01-10
#描述:
#依赖：
#-------------------------------------------------

QT += widgets

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/QCancelLogin.h \
    $$PWD/QCustomWidgetProxy.h \
    qmainwidget.h

SOURCES += \
    $$PWD/QCancelLogin.cpp \
    $$PWD/QCustomWidgetProxy.cpp \
    main.cpp \
    qmainwidget.cpp


build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/embeddeddialogs
INSTALLS += target

FORMS += \
    qmainwidget.ui

RESOURCES += \
    qrc.qrc
