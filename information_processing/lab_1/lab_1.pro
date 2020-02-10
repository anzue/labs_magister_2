TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

SOURCES += \
        files.cpp \
        incedencymatrix.cpp \
        indexvocabulary.cpp \
        logger.cpp \
        main_lab1.cpp \
        main_lab2.cpp \
        main_lab3.cpp \
        mapvocabulary.cpp \
        twowordindex.cpp \
        vocabulary.cpp

HEADERS += \
    coordinvertedindex.h \
    files.h \
    incedencymatrix.h \
    indexvocabulary.h \
    invertindex.h \
    json.hpp \
    logger.h \
    mapvocabulary.h \
    twowordindex.h \
    vocabulary.h

DISTFILES += \
    ReadMe.txt
