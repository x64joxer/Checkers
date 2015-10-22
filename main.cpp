#include "MainWindow.h"
#include <QApplication>
#include "ProgramVariables.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(argc > 1)
       {
        std::string text;

           for(int i = 0; i < argc; i++)
           {
               text = argv[i];
               if (text == "--worker") {ProgramVariables::SetWorker(true); };
           }
       };


    MainWindow w;

    if (!ProgramVariables::IsWorker()) w.show();

    return a.exec();

}
