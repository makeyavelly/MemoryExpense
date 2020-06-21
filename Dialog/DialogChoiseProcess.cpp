#include "DialogChoiseProcess.h"
#include <QProcess>

DialogChoiseProcess::DialogChoiseProcess(const QString &title, QWidget *parent) :
    DialogComboBox(title, getListProcess(), parent)
{
}

QList<DialogComboBox::Value> DialogChoiseProcess::getListProcess() const
{
#ifdef __linux
    QList<Value> res;
    QProcess process;
    process.start("ps -o %p%c");
    process.waitForFinished();
    QStringList answer = QString::fromLocal8Bit(process.readAll()).split("\n");
    answer.removeFirst();
    for (const QString &proc : answer) {
        QStringList procValue = proc.trimmed().split(" ");
        if (procValue.count() > 1) {
            res.push_back(Value(procValue.last(), procValue.first()));
        }
    }
    return res;
#else
    return QList<Value>();
#endif
}
