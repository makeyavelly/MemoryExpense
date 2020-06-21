#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QSettings>
#include "Dialog/DialogChoiseProcess.h"
#include "Service/Service.h"

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
    setGeometry(ini.value("WINDOW/x", 0).toInt(), ini.value("WINDOW/y", 0).toInt(),
                ini.value("WINDOW/w", 500).toInt(), ini.value("WINDOW/h", 300).toInt());
}

void MainWindow::saveSettings()
{
    QSettings ini;
    ini.setValue("PROC/name", procName);
    ini.setValue("WINDOW/x", geometry().x());
    ini.setValue("WINDOW/y", geometry().y());
    ini.setValue("WINDOW/w", geometry().width());
    ini.setValue("WINDOW/h", geometry().height());
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
    memoryMin = -1;
    memoryMax = -1;
    ui->plot->clear();
}

void MainWindow::analizeMemory()
{
    long memory = getMemoryExpense(procPid);
    memoryMin = memoryMin < 0 ? memory : qMin(memory, memoryMin);
    memoryMax = memoryMax < 0 ? memory : qMax(memory, memoryMax);
    ui->plot->appendValue(memory);
    ui->plot->update();
    ui->statusbar->showMessage(QString("Используемая память: %1; мин: %2; макс: %3")
                               .arg(getTextValue(memory, "Б", 1024))
                               .arg(getTextValue(memoryMin, "Б", 1024))
                               .arg(getTextValue(memoryMax, "Б", 1024)));
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
    analizeMemory();
}
