TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -L/usr/local/lib

SOURCES += \
        main.cpp

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
