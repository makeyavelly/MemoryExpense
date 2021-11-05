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
    process.start("ps",  {"-o", "%c%p"});
    process.waitForFinished();
    QStringList answer = QString::fromLocal8Bit(process.readAll()).split("\n");
    answer.removeFirst();
    answer.sort(Qt::CaseInsensitive);
    for (const QString &proc : answer) {
        QStringList procValue = proc.trimmed().split(" ");
        if (procValue.count() > 1) {
            res.push_back(Value(procValue.first(), procValue.last()));
        }
    }
    return res;
#else
    return QList<Value>();
#endif
}
