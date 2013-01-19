#-------------------------------------------------
#
# Project created by QtCreator 2012-06-05T20:51:35
#
#-------------------------------------------------

QT       += core gui

TARGET = test_cmd_voit
TEMPLATE = app


SOURCES += main.cpp\
        principale.cpp \
    fenexec.cpp \
    gestionAffichage.cpp

HEADERS  += principale.hpp \
    fenexec.hpp \
    gestionAffichage.hpp

FORMS    += principale.ui \
    fenexec.ui
 INCLUDEPATH += /usr/include/
 LIBS += -L/usr/lib/ -lSDL
