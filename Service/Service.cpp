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

QString getTextValue(long value, const QString &suffix, int step)
{
    int level = 0;
    double v = value;
    while (long(v) / step > 0) {
        ++level;
        v = double(v) / step;
    }
    QString suf = suffix;
    if (level == 1) suf.push_front("к");
    if (level == 2) suf.push_front("М");
    if (level == 3) suf.push_front("Г");
    if (level == 4) suf.push_front("Т");
    return QString("%1 %2").arg(QString::number(v, 'f', level == 0 ? 0 : 2)).arg(suf);
}
