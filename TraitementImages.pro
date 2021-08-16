#-------------------------------------------------
#
# Project created by QtCreator 2012-12-04T23:11:26
#
#-------------------------------------------------

QT       += core gui

TARGET = TraitementImages
TEMPLATE = app

CONFIG += qxt
QXT += core gui

INCLUDEPATH += $(QXT_DIR)/include/QxtCore
INCLUDEPATH += $(QXT_DIR)/include/QxtGui
INCLUDEPATH += C:/QtSDK/Qxt/include/QxtCore
INCLUDEPATH += C:/QtSDK/Qxt/include/QxtGui

SOURCES += main.cpp\
        mainwindow.cpp \
    modelecouleur.cpp \
    quantification.cpp \
    echantillonnage.cpp \
    transformationgeometrique.cpp \
    detectioncontours.cpp \
    fenetreimagetraitee.cpp \
    ../../Commun/Image/cimage.tpp \
    opmorphomaths.cpp

HEADERS  += mainwindow.h \
    modelecouleur.h \
    quantification.h \
    echantillonnage.h \
    transformationgeometrique.h \
    detectioncontours.h \
    fenetreimagetraitee.h \
    ../../Commun/Image/cimage.h \
    opmorphomaths.h

LIBS += -L../../Commun/Maths/qrealfourier/lib/ -LC:\QtSDK\Qxt\lib\mingw
LIBS += -lqrealfourier -lQxtCore -lQxtGui
