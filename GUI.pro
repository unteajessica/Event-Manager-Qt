QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    EventListView.cpp \
    action.cpp \
    chartwidget.cpp \
    code/controller.cpp \
    code/event.cpp \
    code/repo.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    EventListView.h \
    action.h \
    chartwidget.h \
    code/CSVWriteToFile.h \
    code/HTMLWriteToFile.h \
    code/WriteToFile.h \
    code/controller.h \
    code/event.h \
    code/eventValidator.h \
    code/repo.h \
    code/repoException.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    build/Desktop_Qt_6_9_0_MSVC2022_64bit-Debug/events.csv \
    build/Desktop_Qt_6_9_0_MSVC2022_64bit-Debug/events.html \
    build/Desktop_Qt_6_9_0_MSVC2022_64bit-Debug/events.txt \
    build/Desktop_Qt_6_9_0_MSVC2022_64bit-Debug/user_events.txt
