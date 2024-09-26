QT       += core gui multimedia multimediawidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    baidu_voice.cpp \
    main.cpp \
    my_first.cpp \
    my_next.cpp \
    page_3.cpp \
    page_4.cpp

HEADERS += \
    baidu_voice.h \
    my_first.h \
    my_next.h \
    page_3.h \
    page_4.h

FORMS += \
    my_first.ui \
    my_next.ui \
    page_3.ui \
    page_4.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
