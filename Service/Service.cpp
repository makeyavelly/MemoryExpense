#include "Service.h"
#include <QProcess>

int getPidProcess(const QString &name)
{
#ifdef __linux
    QProcess process;
    process.start(QString("pgrep %1").arg(name));
    process.waitForFinished();
    return process.readAll().toInt();
#else
    return 0;
#endif
}

long getMemoryExpense(int pid)
{
#ifdef __linux
    QProcess process;
    process.start(QString("ps --pid %1 -o rss").arg(pid));
    process.waitForFinished();
    return QString::fromLocal8Bit(process.readAll()).trimmed().split("\n").last().toLong() * 1024;
#else
    return 0;
#endif
}
