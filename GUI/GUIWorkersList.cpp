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
       unsigned int size = WorkerAgent::Size();

       for (unsigned int i = 0; i < size; i++)
       {
            tmp = WorkerAgent::AT(i);
            ui->workersList->addItem(tmp.GetHost().toString() + ":" + QString::number(tmp.GetPort()));
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
