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
            str = tmp.GetHost().toString() + ":" + QString::number(tmp.GetPort());

            if (tmp.GetState() == Peers::STATE::NONE)
            {
                str += "     NONE";
            } else
            if (tmp.GetState() == Peers::STATE::BUSY)
            {
                str += "     BUSY";
            } else
            if (tmp.GetState() == Peers::STATE::FREE)
            {
                str += "     FREE";
            }

            ui->workersList->addItem(str);
       }
    }
}

GUIWorkersList::~GUIWorkersList()
{
    delete refreschTimer;
    delete ui;
}

void GUIWorkersList::on_OKButton_clicked()
{
    this->deleteLater();
}
