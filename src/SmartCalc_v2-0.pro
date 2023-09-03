QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += view/qcustomplot_lib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cc \
    main.cc \
    model/credit_calculation.cc \
    model/deposit_calculation.cc \
    model/model.cc \
    model/calculate.cc \
    model/parser.cc \
    model/validator.cc \
    view/creditcalc.cc \
    view/depositcalc.cc \
    view/graphwindow.cc \
    view/mainwindow.cc \
    view/qcustomplot_lib/qcustomplot.cc

HEADERS += \
    controller/controller.h \
    model/model.h \
    model/validator_lib/exprtk.hpp \
    view/creditcalc.h \
    view/depositcalc.h \
    view/graphwindow.h \
    view/mainwindow.h \
    view/qcustomplot_lib/qcustomplot.h

FORMS += \
    view/creditcalc.ui \
    view/depositcalc.ui \
    view/graphwindow.ui \
    view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    view/resources/anime_girl.qrc
