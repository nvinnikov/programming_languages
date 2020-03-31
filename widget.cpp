#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_quitButton_clicked()
{
    close();
}

void Widget::on_startButton_clicked()
{
    ui->field->start();
}

void Widget::on_field_latitudeChanged(double latitude)
{
    ui->latitude->setPlainText(QString::number(latitude, 'd', 9));
}

void Widget::on_field_longitudeChanged(double longtitude)
{
    ui->longitude->setPlainText(QString::number(longtitude, 'd', 9));
}

void Widget::on_field_tableChanged(const QString& s)
{
    ui->skyview->setText(s);
}

void Widget::on_field_statusChanged(const QString& status)
{
    ui->status->setPlainText(status);
}

void Widget::on_field_numSettlersChanged(int num)
{
    ui->satellites->setPlainText(QString::number(num));
}
