QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Dialog/DialogChoiseProcess.cpp \
    Dialog/DialogComboBox.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Dialog/DialogChoiseProcess.h \
    Dialog/DialogComboBox.h \
    MainWindow.h

FORMS += \
    Dialog/DialogComboBox.ui \
    MainWindow.ui

DISTFILES += \
    TODO.txt

RESOURCES += \
    icons.qrc
