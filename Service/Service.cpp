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
    process.start(QString("top -b -n 1 -p %1").arg(pid));
    process.waitForFinished();
    QString answer = QString::fromLocal8Bit(process.readAll().trimmed()).split("\n").last().trimmed();
    QStringList params = answer.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    if (params.count() > 6) {
        return 1024 * (params.at(5).toLong() - params.at(6).toLong());
    }
    return 0;
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
