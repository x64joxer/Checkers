#ifndef GUIWORKERSLIST_H
#define GUIWORKERSLIST_H

#include <QDialog>
#include <QTimer>
#include <QDebug>
#include "TCP/WorkerAgent.h"

namespace Ui {
class GUIWorkersList;
}

class GUIWorkersList : public QDialog
{
    Q_OBJECT

    public:
        explicit GUIWorkersList(QWidget *parent = 0);
        ~GUIWorkersList();

    private slots:
       void RefreshList();

       void on_OKButton_clicked();

private:
        Ui::GUIWorkersList *ui;
        QTimer *refreschTimer;
};

#endif // GUIWORKERSLIST_H
