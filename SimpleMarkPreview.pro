#-------------------------------------------------
#
# Project created by QtCreator 2014-07-22T16:54:54
#
#-------------------------------------------------

QT += core gui webkit
#QT += webkitwidgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleMarkPreview
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    smp_parse.h

FORMS    +=



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/discount/release/ -lmarkdown
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/discount/debug/ -lmarkdown
else:unix: LIBS += -L$$PWD/discount/ -lmarkdown

INCLUDEPATH += $$PWD/discount
DEPENDPATH += $$PWD/discount

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/discount/release/libmarkdown.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/discount/debug/libmarkdown.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/discount/release/markdown.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/discount/debug/markdown.lib
else:unix: PRE_TARGETDEPS += $$PWD/discount/libmarkdown.a

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    markdown_sample.txt \
    markdown_base.txt
