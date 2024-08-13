QT       += core sql gui widgets

TARGET    = "SQL view"
CONFIG   -= console
CONFIG   -= app_bundle

RC_ICONS = SQL.ico

TEMPLATE = app

ios {
    CONFIG(debug, debug|release) {
        LIBS += -lsqlitecipher_debug
    } else {
        LIBS += -lsqlitecipher
    }
}

SOURCES += main.cpp \
    qdatabaseform.cpp

FORMS += \
    qdatabaseform.ui

HEADERS += \
    qdatabaseform.h

RESOURCES += \
    img.qrc
