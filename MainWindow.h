#pragma once

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer timer;
    QString procName;
    int procPid;

    long memory;
    long memoryMin;
    long memoryMax;
    long memoryFix;
    long memoryFixMin;
    long memoryFixMax;
    long memoryFixBusy;
    long memoryFixFree;
    long memoryFixDelta;

    void loadSettings();
    void saveSettings();

    void setProc(int pid, const QString &name);
    void startAnalize();

    void analizeMemory();
    QString getTextMemoryValue(long value) const;

private slots:
    void slotAnalize();
    void on_actionChoiseProc_triggered();
    void on_actionFix_triggered();
};
