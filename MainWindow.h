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

    long memoryMin;
    long memoryMax;

    void loadSettings();
    void saveSettings();

    void setProc(int pid, const QString &name);
    void startAnalize();

    void analizeMemory();

private slots:
    void on_actionChoiseProc_triggered();
    void slotAnalize();
};
