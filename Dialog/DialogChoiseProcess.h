#pragma once

#include "DialogComboBox.h"

class DialogChoiseProcess : public DialogComboBox
{
    Q_OBJECT

public:
    explicit DialogChoiseProcess(const QString &title, QWidget *parent = nullptr);

private:
    QList<Value> getListProcess() const;
};

