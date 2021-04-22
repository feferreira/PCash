QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    carteiramodel.cpp \
    corretora.cpp \
    data.cpp \
    main.cpp \
    operacao.cpp \
    pgconnection.cpp \
    proventos.cpp \
    widget.cpp

HEADERS += \
    INIReader.h \
    carteiramodel.h \
    corretora.h \
    data.h \
    operacao.h \
    pgconnection.h \
    proventos.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
