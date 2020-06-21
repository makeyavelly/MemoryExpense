#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QSettings>
#include "Dialog/DialogChoiseProcess.h"
#include "Service/Service.h"
#include <QDebug> //delete

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , procName()
    , procPid(0)
{
    ui->setupUi(this);
    ui->plot->setStepLevel(1024);
    ui->plot->setSuffix("Б");
    loadSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::loadSettings()
{
    QSettings ini;
    QString procName = ini.value("PROC/name", QString()).toString();
    if (!procName.isEmpty()) {
        int pid = getPidProcess(procName);
        if (pid) {
            setProc(pid, procName);
            startAnalize();
        }
    }
}

void MainWindow::saveSettings()
{
    QSettings ini;
    ini.setValue("PROC/name", procName);
}

void MainWindow::setProc(int pid, const QString &name)
{
    procPid = pid;
    procName = name;
    ui->labelProcName->setText(QString("Выбран процесс <u>%1</u> PID <u>%2</u>").arg(name).arg(pid));
}

void MainWindow::startAnalize()
{
    if (!timer.isActive()) {
        QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(slotAnalize()));
        timer.start(1000);
    }
    ui->plot->clear();
}

void MainWindow::on_actionChoiseProc_triggered()
{
    DialogChoiseProcess dialog("Выбор процесса", this);
    if (dialog.exec() == QDialog::Accepted) {
        setProc(dialog.getValue().toInt(), dialog.getName());
        startAnalize();
    }
}

void MainWindow::slotAnalize()
{
    ui->plot->appendValue(getMemoryExpense(procPid));
    ui->plot->update();
}
