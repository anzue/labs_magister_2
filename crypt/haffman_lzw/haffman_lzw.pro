TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Huffman.cpp \
        LZW.cpp \
        defines.cpp \
        main.cpp

HEADERS += \
    Huffman.h \
    LZW.h \
    defines.h
