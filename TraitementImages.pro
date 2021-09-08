#-------------------------------------------------
#
# Project created by QtCreator 2012-12-04T23:11:26
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = TraitementImages
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    ColorModel.cpp \
    Quantisation.cpp \
    Sampling.cpp \
    GeometricTransformation.cpp \
    EdgeDetection.cpp \
    TreatedImageWindow.cpp \
    ../../Commun/Image/cimage.tpp \
    OpMorphoMaths.cpp \
    RegionDetection.cpp

HEADERS  += MainWindow.h \
    ColorModel.h \
    Quantisation.h \
    Sampling.h \
    GeometricTransformation.h \
    EdgeDetection.h \
    TreatedImageWindow.h \
    ../../Commun/Image/cimage.h \
    OpMorphoMaths.h \
    RegionDetection.h

LIBS += -L../../Commun/Maths/build/
LIBS += -lqrealfourier
