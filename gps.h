#ifndef GPS_H
#define GPS_H

#include <iostream>
#include <sstream>

#include <libgpsmm.h>

#include <QWidget>
#include <QBasicTimer>
#include <QTimerEvent>
#include <QTimer>
#include <QEvent>
#include <QPen>
#include <QtMultimedia/QSound>
#include <QPainter>
#include <vector>
#include <QGraphicsScene>
#include <QtMath>
#include <QTableWidget>
#include <QVector>

class gps : public QWidget
{
    Q_OBJECT
public:
    explicit gps(QWidget *parent = nullptr);

private:
    int seconds;
    int seconds_sat;
    double latitude;
    double longitude;
    int azimuth;
    double elevation;

    gpsmm gps_rec;

    QBasicTimer timer;
    QSound beep;
    QVector<QPair<double,double>> points;
    
signals:
    // TODO: check types!
    void latitudeChanged(double latitude);
    void longitudeChanged(double longitude);
    void tableChanged(const QString& s);
    void statusChanged(const QString& status);
    void numSettlersChanged(int num);
    
public slots:
    void start();

protected:
    void timerEvent(QTimerEvent* e) override;
    void paintEvent(QPaintEvent* e) override;

};

#endif // GPS_H
