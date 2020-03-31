#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

public slots:
    void on_quitButton_clicked();
    void on_startButton_clicked();
    void on_field_latitudeChanged(double latitude);
    void on_field_longitudeChanged(double longtitude);
    void on_field_tableChanged(const QString& s);
    void on_field_statusChanged(const QString& status);
    void on_field_numSettlersChanged(int num);
};
#endif // WIDGET_H
