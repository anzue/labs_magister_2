TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

SOURCES += \
        compressedinvertindex.cpp \
        compressedvocabulary.cpp \
        files.cpp \
        incedencymatrix.cpp \
        indexvocabulary.cpp \
        logger.cpp \
        main_lab1.cpp \
        main_lab2.cpp \
        main_lab3.cpp \
        main_lab4.cpp \
        main_lab_spimi_index.cpp \
        main_zone_range_lab.cpp \
        mapvocabulary.cpp \
        ngramindex.cpp \
        permutationindex.cpp \
        spimiindex.cpp \
        twowordindex.cpp \
        vocabulary.cpp \
        wordtree.cpp \
        zoneranger.cpp

HEADERS += \
    compressedinvertindex.h \
    compressedvocabulary.h \
    coordinvertedindex.h \
    files.h \
    incedencymatrix.h \
    indexvocabulary.h \
    invertindex.h \
    invertindexfunctions.h \
    json.hpp \
    logger.h \
    mapvocabulary.h \
    ngramindex.h \
    permutationindex.h \
    spimiindex.h \
    twowordindex.h \
    vocabulary.h \
    wordtree.h \
    zoneranger.h

DISTFILES += \
    ReadMe.txt
