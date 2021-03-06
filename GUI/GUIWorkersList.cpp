#include "GUI/GUIWorkersList.h"
#include "ui_GUIWorkersList.h"

GUIWorkersList::GUIWorkersList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GUIWorkersList)
{
    ui->setupUi(this);

    refreschTimer = new QTimer();
    refreschTimer->setInterval(1000);
    connect(refreschTimer,SIGNAL(timeout()), this, SLOT(RefreshList()));
    refreschTimer->start();
}

void GUIWorkersList::RefreshList()
{
   ui->workersList->clear();

   if (WorkerAgent::Size() > 0)
    {
       Peers tmp;
       QString str;
       unsigned int size = WorkerAgent::Size();

       for (unsigned int i = 0; i < size; i++)
       {
            tmp = WorkerAgent::AT(i);

            if (!tmp.IsNull())
            {
                str = "IP ADRESS: " + tmp.GetHost().toString() + ":" + QString::number(tmp.GetPort());

                str+= "     NUMBER OF THREAD: " + QString::number(tmp.GetNumOThread());

                str += "     STATE: ";
                if (tmp.GetState() == Peers::STATE::NONE)
                {
                    str += " NONE";
                } else
                if (tmp.GetState() == Peers::STATE::BUSY)
                {
                    str += " BUSY";
                } else
                if (tmp.GetState() == Peers::STATE::FREE)
                {
                    str += " FREE";
                }

                ui->workersList->addItem(str);
            }
       }
    }
}

void GUIWorkersList::on_OKButton_clicked()
{
    this->deleteLater();
}

void GUIWorkersList::on_spinBoxMaxWorkers_valueChanged(int arg1)
{
    ProgramVariables::SetMaxWorkers(arg1);
}

GUIWorkersList::~GUIWorkersList()
{
    delete refreschTimer;
    delete ui;
}
