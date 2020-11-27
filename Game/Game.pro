TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia testlib

CONFIG += c++14

SOURCES += \
    betteractoritem.cpp \
    enddialog.cpp \
    gameview.cpp \
    gamewindow.cpp \
    main.cc \
    player.cpp \
    startdialog.cpp \
    statistics.cpp \
    tampere.cpp

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

HEADERS += \
    betteractoritem.h \
    enddialog.h \
    gameview.hh \
    gamewindow.hh \
    player.hh \
    startdialog.h \
    statistics.h \
    tampere.hh

FORMS += \
    enddialog.ui \
    gamewindow.ui \
    startdialog.ui
