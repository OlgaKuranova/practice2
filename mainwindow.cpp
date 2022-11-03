#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace
{
    double windowCapacity_ = 0.95;

    int Computed_dot1 = 7;
    int Computed_dot2 = 17;
    int Computed_dot3 = 5;

    double line_width1 = 0.015;
    double line_length1 = -0.6;
    double line_width2 = 0.013;
    double line_length2 = -0.75;
    double line_width3 = 0.01;
    double line_length3 = -0.9;
    double frequency = 6.0;

    int circle_coord = -5;
    int circle_size = 12;

    auto color_hour = Qt::black;
    auto color_minute = Qt::black;
    auto color_second = Qt::red;

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer -> start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

 QPainter draw;

 //функция отрисовки стрелок
void MainWindow::drawArrow(double line_width, double line_length, double rotate){

    int r = windowCapacity_ * qMin(width()/2, height()/2);
    draw.setPen(Qt::NoPen); //исключаем контур фигуры
    QPolygon pol;
    pol << QPoint(-line_width*r, 0) << QPoint(line_width*r, 0) << QPoint(line_width*r, line_length*r) << QPoint(-line_width*r, line_length*r); //(толщина, длина)
    draw.rotate(rotate);
    draw.drawPolygon(pol);
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QTime time = QTime::currentTime();

    draw.begin(this);

    draw.setRenderHint(QPainter::Antialiasing); //сглаживание картинки

    draw.translate(width()/2, height()/2); //перемешение центра координат в центр

    int r = windowCapacity_ * qMin(width()/2, height()/2);// radius

    for(int i = 0; i < 60; i++)
    {
        if (i % 5 == 0)
        {
          draw.setPen(QColor(0, 0, 0, 255));
          draw.drawLine(0, r + Computed_dot1, 0, r - Computed_dot2); //(х1, у1, х2, у2)

        }
        else
        {
          draw.setPen(QColor(200, 0, 0, 200)); //(red, green, blue, прозрачность)
          draw.drawLine(0, r + Computed_dot1, 0, r - Computed_dot3);
        }
        draw.rotate(frequency); //частота прорисовки линий
    }


    // часовая стрелка
    draw.save();
    draw.setBrush(QColor(color_hour));
    drawArrow(line_width1, line_length1, (30 * (time.hour() + time.minute()/60)) );
    draw.restore();


    // минутная стрелка
    draw.save();
    draw.setBrush(QColor(color_minute));
    drawArrow(line_width2, line_length2, ( frequency * (time.minute()+ time.second()/60)) );
    draw.restore();


    // секундная стрелка
    draw.save();
    draw.setBrush(QColor(color_second));
    drawArrow(line_width3, line_length3, (frequency * time.second()) );
    draw.restore();


    //круг посередине
    draw.save();
    draw.setPen(Qt::NoPen);
    draw.setBrush(QColor(Qt::red));
    draw.drawEllipse(circle_coord, circle_coord, circle_size, circle_size);
    draw.restore();


    draw.end();
}
