#pragma once

#include <QDialog>
#include <QVariant>

namespace Ui {
class DialogComboBox;
}


class DialogComboBox : public QDialog
{
    Q_OBJECT

public:
    using Value = QPair<QString, QVariant>;

    explicit DialogComboBox(const QString &title, const QList<Value> &variants, QWidget *parent = nullptr);
    ~DialogComboBox();

    Value get() const;
    QString getName() const;
    QVariant getValue() const;

private:
    Ui::DialogComboBox *ui;

    void fillComboBox(const QList<Value> &variants);

private slots:
    void on_btOk_clicked();
    void on_btCancel_clicked();
};

