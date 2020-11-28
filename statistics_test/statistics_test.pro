QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += ../Game/statistics.h

SOURCES +=  tst_statistics_test.cpp \
            ../Game/statistics.cpp

INCLUDEPATH += \
    ../Game/ \
    $$PWD/../Course/CourseLib
