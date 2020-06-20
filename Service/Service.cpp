#include "Service.h"
#include <QProcess>

long getMemoryExpense(int pid)
{
#ifdef __linux
    QProcess process;
    process.start(QString("ps --pid %1 -o rss").arg(pid));
    process.waitForFinished();
    return QString::fromLocal8Bit(process.readAll()).trimmed().split("\n").last().toLong();
#else
    return 0;
#endif
}
