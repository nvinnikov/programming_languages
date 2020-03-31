#include "gps.h"

gps::gps(QWidget *parent) :
    QWidget(parent),
    gps_rec(gpsmm("localhost", DEFAULT_GPSD_PORT)),
    beep("/home/nikita/Downloads/nikita228/beep.wav")
{

    if (gps_rec.stream(WATCH_ENABLE | WATCH_JSON) == nullptr) {
        std::cerr << "No GPSD running.\n";
    }

}

void gps::start()
{
    timer.start(500, this);
    seconds = 0;
    seconds_sat = 0;
    latitude = -1;
    longitude = -1;
//    azimuth = 0;
//    elevation = 0;

    emit latitudeChanged(latitude);
    emit longitudeChanged(longitude);
    emit statusChanged("NO_FIX");
    emit numSettlersChanged(0);
//    emit azimuthChanged(azimuth);
//    emit elevationChanged(elevation);
}

void gps::timerEvent(QTimerEvent *e)
{
    if (e->timerId() == timer.timerId()) {
        ++seconds;
        struct gps_data_t *gpsd_data = gps_rec.read();
        if (gpsd_data == nullptr) {
            emit tableChanged("No Data!\nCan not read GPSD data for " + QString::number(seconds/2) + " seconds");
            emit statusChanged("CANT_READ");
        }
        else {
            points.clear();

            ++seconds_sat;
            seconds = 0;

            latitude = gpsd_data->fix.latitude;
            longitude = gpsd_data->fix.longitude;

            emit statusChanged((gpsd_data->status) ? "FIX" : "NO_FIX");
            emit latitudeChanged(latitude);
            emit longitudeChanged(longitude);

            if (gpsd_data->satellites_used != 0) {
                beep.play();
                seconds_sat = 0;
                emit numSettlersChanged(gpsd_data->satellites_used);
                QString s;
                for (int i = 0; i < gpsd_data->satellites_used; ++i) {
                    azimuth = gpsd_data->skyview[i].azimuth;
                    elevation = gpsd_data->skyview[i].elevation;
                    double x0 = (elevation * 5) * qCos(azimuth);
                    double y0 = (elevation * 5) * qSin(azimuth);
                    points.push_back(QPair<double,double>{x0, y0});
                    //points += QPair<double,double>{-x0, -y0};
                    s += QString::number(i) + '\n' +
                            "azimuth: " + QString::number(gpsd_data->skyview[i].azimuth) + '\n' +
                            "elevation: " + QString::number(gpsd_data->skyview[i].elevation) + '\n';
                }
                emit tableChanged(s);
            }
            else if (seconds_sat > 20)
            {
                emit numSettlersChanged(0);
                emit tableChanged("No Data!\nWaiting for " + QString::number(seconds_sat/2) + " seconds");
            }
        }
        update();
    }
    else {
        QWidget::timerEvent(e);
    }
}

void gps::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter painter(this);
    QGraphicsScene scene;

    scene.addRect(QRectF(0, 0, 800, 800), QPen{Qt::black,4});

    scene.addEllipse(QRectF(0, 0, 800, 800), QPen{Qt::black,8});

    for (auto& p : points) {
//        std::cerr << p.first << ' ' << p.second << '\n';
        scene.addEllipse(QRectF(400 + p.first - 15, 400 + p.second - 15, 30, 30), QPen{Qt::red,12}, Qt::red);
    }

    painter.setRenderHint(QPainter::Antialiasing);
    scene.render(&painter);

}
