INCLUDEPATH += $$quote(D:/SVP/Kurs/Kursovaya)
SOURCES += $$quote(D:/SVP/Kurs/Kursovaya/qcustomplot.cpp)
HEADERS += $$quote(D:/SVP/Kurs/Kursovaya/qcustomplot.h)

QT += widgets printsupport

LIBS += -LC:/Qt/Qt5.12.12/5.12.12/mingw73_32/lib \
        -lmingw32 \
        -lqtmain \
        -lQt5Core \
        -lQt5Gui \
        -lQt5Widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
LIBS += -lQt5PrintSupport

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=  \
    main.cpp \
    mainwindow.cpp

HEADERS +=  \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
