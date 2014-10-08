#-------------------------------------------------
#
# Project created by QtCreator 2014-07-22T16:54:54
#
#-------------------------------------------------

QT += core gui webkit
#QT += webkitwidgets

CONFIG += debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = SimpleMarkPreview
TEMPLATE = app

SOURCES += src/main.cpp\
           src/mainwindow.cpp

HEADERS  += include/mainwindow.h \
            include/smp_parse.h

FORMS    +=

INCLUDEPATH += include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/discount/release/ -lmarkdown
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/discount/debug/ -lmarkdown
else:unix: LIBS += -L$$PWD/lib/discount/ -lmarkdown

INCLUDEPATH += $$PWD/lib/discount
DEPENDPATH += $$PWD/lib/discount

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/discount/release/libmarkdown.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/discount/debug/libmarkdown.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/discount/release/markdown.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/discount/debug/markdown.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/discount/libmarkdown.a

RESOURCES += \
    resources/resources.qrc

OTHER_FILES += \
    resources/markdown_sample.txt \
    resources/markdown_base.txt
