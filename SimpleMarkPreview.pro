#-------------------------------------------------
#
# Project created by QtCreator 2014-07-22T16:54:54
#
#-------------------------------------------------

CONFIG += debug

QT += core gui webkit

# For Qt5, naming changes
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

QMAKE_CXXFLAGS += -fno-strict-aliasing -Wno-unused-parameter

TARGET = SimpleMarkPreview
TEMPLATE = app

SOURCES += src/main.cpp\
           src/mainwindow.cpp \
    lib/cpp-markdown/markdown-tokens.cpp \
    lib/cpp-markdown/markdown.cpp

HEADERS  += include/mainwindow.h \
            include/smp_parse.h \
    lib/cpp-markdown/markdown.h \
    lib/cpp-markdown/markdown-tokens.h

FORMS    +=

INCLUDEPATH += include
INCLUDEPATH += lib/cpp-markdown

unix: LIBS += -lboost_regex

RESOURCES += \
    resources/resources.qrc

OTHER_FILES += \
    resources/markdown_sample.txt \
    resources/markdown_base.txt
