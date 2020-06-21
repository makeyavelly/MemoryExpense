QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Diagram/Plot.cpp \
    Dialog/DialogChoiseProcess.cpp \
    Dialog/DialogComboBox.cpp \
    Service/Service.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Diagram/Plot.h \
    Dialog/DialogChoiseProcess.h \
    Dialog/DialogComboBox.h \
    MainWindow.h \
    Service/Service.h

FORMS += \
    Dialog/DialogComboBox.ui \
    MainWindow.ui

DISTFILES += \
    TODO.txt

RESOURCES += \
    icons.qrc
