#-------------------------------------------------
#
# Project created by QtCreator 2015-06-07T21:47:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Checkers
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    CheckerArea.cpp \
    Board.cpp \
    Pawn.cpp \
    Logs.cpp \
    SinglePath.cpp \
    PawnPos.cpp \
    PossibleMoves.cpp \
    IA/IADecisionTree.cpp \
    IA/IAPossibleMoves.cpp \
    IA/IATreeExpander.cpp \
    IA/IABoardQueue.cpp

HEADERS  += MainWindow.h \
    CheckerArea.h \
    Board.h \
    Pawn.h \
    Logs.h \
    SinglePath.h \
    PawnPos.h \
    PossibleMoves.h \
    IA/IADecisionTree.h \
    IA/IAPossibleMoves.h \
    IA/IATreeExpander.h \
    IA/IABoardQueue.h

FORMS    += MainWindow.ui \
    CheckerArea.ui
