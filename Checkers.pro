#-------------------------------------------------
#
# Project created by QtCreator 2015-06-07T21:47:32
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Checkers
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    CheckerArea.cpp \
    Board.cpp \
    Pawn.cpp \
    PawnPos.cpp \
    PossibleMoves.cpp \
    IA/IAPossibleMoves.cpp \
    Traces/Traces.cpp \
    ThreadIA/ThreadIASimpleBoard.cpp \
    ThreadIA/ThreadIATreeExpander.cpp \
    ThreadIA/ThreadIABoardQueue.cpp \
    ThreadIA/ThreadIAMove.cpp \
    Tests/PerformanceTests.cpp \
    Tests/FunctionTests.cpp \
    ProgramVariables.cpp \
    TCP/ServerTCP.cpp \
    TCP/WorkerTCP.cpp \
    TCP/MessageHandler.cpp \
    TCP/Peers.cpp \
    TCP/PeerQueue.cpp \
    TCP/MessageForwarder.cpp

HEADERS  += MainWindow.h \
    CheckerArea.h \
    Board.h \
    Pawn.h \
    PawnPos.h \
    PossibleMoves.h \
    IA/IAPossibleMoves.h \
    Traces/Traces.h \
    ThreadIA/ThreadIASimpleBoard.h \
    ThreadIA/ThreadIATreeExpander.h \
    ThreadIA/ThreadIABoardQueue.h \
    ThreadIA/ThreadIAMove.h \
    Tests/PerformanceTests.h \
    Tests/FunctionTests.h \
    ProgramVariables.h \
    TCP/ServerTCP.h \
    TCP/WorkerTCP.h \
    TCP/MessageHandler.h \
    TCP/Peers.h \
    TCP/PeerQueue.h \
    TCP/MessageForwarder.h

FORMS    += MainWindow.ui \
    CheckerArea.ui
