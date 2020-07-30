#ifndef FORM_H
#define FORM_H
#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include "system.h"
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_spectrocurve.h>
#include <QVector>
#include <qwt_point_3d.h>
#include <qwt_color_map.h>
class Form : public QWidget
{
    Q_OBJECT
public:
    Form(QWidget *parent = 0);
    ~Form();
private:
    QLabel * labelSize;
    QLabel * labelPhiLeft;
    QLabel * labelPhiRight;
    QLabel * labelPhiDown;
    QLabel * labelPhiTop;
    QLabel * labelNumGrid;

    QDoubleSpinBox * doubleSpinBoxSize;
    QDoubleSpinBox * doubleSpinBoxPhiLeft;
    QDoubleSpinBox * doubleSpinBoxPhiRight;
    QDoubleSpinBox * doubleSpinBoxPhiDown;
    QDoubleSpinBox * doubleSpinBoxPhiTop;
    QDoubleSpinBox * doubleSpinBoxNumGrid;

    QPushButton * pushButtonStart;

    QTextEdit * textEditLog;
    System * sys;

    QwtPlot * plot;
    QwtPlotSpectroCurve *curve;
    QVector<QwtPoint3D> data;


    //Карта цветов необходима, чтобы задать цвета максимального
    //и минимального значений, там же можно управлять и
    //дополнительными настройками. ColorMap - наследник
    //QwtLinearColorMap. Экземпляр последнего не можно просто
    //так создать - он абстрактный. Описание ColorMap - ниже


public slots:
    void startCalculation();
};
class ColorMap: public QwtLinearColorMap
{
public:
    ColorMap():
        QwtLinearColorMap( Qt::darkBlue, Qt::red )
           {
               addColorStop( 0.01, Qt::blue );
               addColorStop( 0.02, Qt::darkCyan );
               addColorStop( 0.05, Qt::cyan );
               addColorStop( 0.1, Qt::darkGreen );
               addColorStop( 0.4, Qt::green );
               addColorStop( 0.5, Qt::darkYellow );
               addColorStop( 0.6, Qt::yellow );
               addColorStop( 0.7, Qt::darkRed );
           }
};

#endif // FORM_H

