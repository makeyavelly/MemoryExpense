#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include "Dialog/DialogChoiseProcess.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , procName()
    , procPid(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setProc(int pid, const QString &name)
{
    procPid = pid;
    procName = name;
    ui->labelProcName->setText(QString("Выбран процесс <u>%1</u> PID <u>%2</u>").arg(name).arg(pid));
}

void MainWindow::on_actionChoiseProc_triggered()
{
    DialogChoiseProcess dialog("Выбор процесса", this);
    if (dialog.exec() == QDialog::Accepted) {
        setProc(dialog.getValue().toInt(), dialog.getName());
    }
}
