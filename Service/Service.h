#pragma once

#include <QString>

int getPidProcess(const QString &name);
long getMemoryExpense(int pid);

QString getTextValue(long value, const QString &suffix, int step = 1000);
