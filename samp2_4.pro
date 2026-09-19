#-------------------------------------------------
#
# Project created by QtCreator 2016-11-14T00:17:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = samp2_4
TEMPLATE = app


SOURCES += main.cpp\
        qwmainwind.cpp

HEADERS  += qwmainwind.h

FORMS    += qwmainwind.ui

RESOURCES += \
    res.qrc

# RC_ICONS = AppIcon.ico
# 注：工程路径含中文，Qt 6.8 + MinGW 的 windres 无法打开该图标（报
# "can't open icon file ... Invalid argument"），导致编译失败，故暂时禁用。
# 程序功能不受影响；如需保留 exe 图标，请把工程移到纯英文路径（如 D:\QT\samp2_4App）后取消注释。
