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
        MainWindow.cpp \
    ColorModel.cpp \
    Quantisation.cpp \
    Sampling.cpp \
    GeometricTransformation.cpp \
    EdgeDetection.cpp \
    TreatedImageWindow.cpp \
    ../../Commun/Image/cimage.tpp \
    OpMorphoMaths.cpp

HEADERS  += MainWindow.h \
    ColorModel.h \
    Quantisation.h \
    Sampling.h \
    GeometricTransformation.h \
    EdgeDetection.h \
    TreatedImageWindow.h \
    ../../Commun/Image/cimage.h \
    OpMorphoMaths.h

LIBS += -L../../Commun/Maths/qrealfourier/lib/ -LC:\QtSDK\Qxt\lib\mingw
LIBS += -lqrealfourier -lQxtCore -lQxtGui
