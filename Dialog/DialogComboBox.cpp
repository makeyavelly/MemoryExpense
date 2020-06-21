#include "DialogComboBox.h"
#include "ui_DialogComboBox.h"

DialogComboBox::DialogComboBox(const QString &title, const QList<Value> &variants, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogComboBox)
{
    ui->setupUi(this);
    setWindowTitle(title);
    fillComboBox(variants);
}

DialogComboBox::~DialogComboBox()
{
    delete ui;
}

DialogComboBox::Value DialogComboBox::get() const
{
    return QPair(getName(), getValue());
}

QString DialogComboBox::getName() const
{
    return ui->combo->currentText();
}

QVariant DialogComboBox::getValue() const
{
    return ui->combo->itemData(ui->combo->currentIndex());
}

void DialogComboBox::fillComboBox(const QList<Value> &variants)
{
    ui->combo->clear();
    for (auto variant : variants) {
        ui->combo->addItem(variant.first, variant.second);
    }
}

void DialogComboBox::on_btOk_clicked()
{
    accept();
}

void DialogComboBox::on_btCancel_clicked()
{
    reject();
}
