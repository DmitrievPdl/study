#include "form.h"
#include <QLayout>
#include<QString>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_color_map.h>
#define pi 3.14

Form::Form(QWidget *parent)
    : QWidget(parent), sys(nullptr)
{
    labelSize = new QLabel(" size ");
    labelPhiLeft = new QLabel("potentioal on left");
    labelPhiRight = new QLabel("potentioal on right");
    labelPhiDown = new QLabel("potentioal on down");
    labelPhiTop = new QLabel("potentioal on top");
    labelNumGrid = new QLabel("the number of nodes in the grid");

    doubleSpinBoxSize = new QDoubleSpinBox;
    doubleSpinBoxPhiLeft = new QDoubleSpinBox;
    doubleSpinBoxPhiRight = new QDoubleSpinBox;
    doubleSpinBoxPhiDown = new QDoubleSpinBox;
    doubleSpinBoxPhiTop = new QDoubleSpinBox;
    doubleSpinBoxNumGrid = new QDoubleSpinBox;


    doubleSpinBoxSize->setSingleStep(1);
    doubleSpinBoxPhiLeft->setSingleStep(0.1);
    doubleSpinBoxPhiRight->setSingleStep(0.1);
    doubleSpinBoxPhiDown->setSingleStep(0.1);
    doubleSpinBoxPhiTop->setSingleStep(0.1);
    doubleSpinBoxPhiLeft->setMaximum(10);
    doubleSpinBoxPhiRight->setMaximum(10);
    doubleSpinBoxPhiDown->setMaximum(10);
    doubleSpinBoxPhiTop->setMaximum(10);
    doubleSpinBoxNumGrid->setSingleStep(1);

    //параметры по умолчанию
    doubleSpinBoxSize->setValue(1);
    doubleSpinBoxPhiLeft->setValue(10);
    doubleSpinBoxPhiRight->setValue(10);
    doubleSpinBoxPhiDown->setValue(10);
    doubleSpinBoxPhiTop->setValue(10);
    doubleSpinBoxNumGrid->setValue(1);

    pushButtonStart = new QPushButton("Start");
    textEditLog = new QTextEdit;
    textEditLog->setReadOnly(true);

    //PLOT
    plot = new QwtPlot;
    plot->setTitle("potential");
    plot->setCanvasBackground(QBrush(Qt::black));

    curve = new QwtPlotSpectroCurve;
    ColorMap *colormap = new ColorMap;
    curve->setColorMap(colormap);
    curve->setColorRange(QwtInterval(0,10));
    curve->attach(plot);

    QwtLegend *legend = new QwtLegend;
    plot->insertLegend(legend);
    //

    QGridLayout * layoutParameters = new QGridLayout;
    layoutParameters->addWidget(labelSize, 0, 0);
    layoutParameters->addWidget(labelPhiLeft, 1, 0);
    layoutParameters->addWidget(labelPhiRight, 2, 0);
    layoutParameters->addWidget(labelPhiDown, 3, 0);
    layoutParameters->addWidget(labelPhiTop, 4, 0);
    //layoutParameters->addWidget(labelNumGrid, 5, 0);

    layoutParameters->addWidget(doubleSpinBoxSize, 0, 1);
    layoutParameters->addWidget(doubleSpinBoxPhiLeft, 1, 1);
    layoutParameters->addWidget(doubleSpinBoxPhiRight, 2, 1);
    layoutParameters->addWidget(doubleSpinBoxPhiDown, 3, 1);
    layoutParameters->addWidget(doubleSpinBoxPhiTop, 4, 1);
    //layoutParameters->addWidget(doubleSpinBoxNumGrid, 5, 1);

    QHBoxLayout * layoutButtons = new QHBoxLayout;
        layoutButtons->addWidget(pushButtonStart);

        QVBoxLayout * layoutLeft = new QVBoxLayout;
        layoutLeft->addLayout(layoutParameters);
        layoutLeft->addLayout(layoutButtons);
        //layoutLeft->addWidget(textEditLog);

        QVBoxLayout *layoutRight = new QVBoxLayout;
        layoutRight->addWidget(plot);

        QHBoxLayout * layoutMain = new QHBoxLayout;
        layoutMain->addLayout(layoutLeft);
        layoutMain->addLayout(layoutRight);

        this->setLayout(layoutMain);

    this->setLayout(layoutMain);
    connect(pushButtonStart, SIGNAL(clicked()), this, SLOT(startCalculation()));
}
Form::~Form()
{

}
void Form::startCalculation()
{
    delete sys;
    data.clear();
    sys = new System(doubleSpinBoxSize->value(), doubleSpinBoxPhiLeft->value(), doubleSpinBoxPhiRight->value(),
                     doubleSpinBoxPhiDown->value(), doubleSpinBoxPhiTop->value(), doubleSpinBoxNumGrid->value());

    sys->iterationMethod();
    for (int i = 0; i < DIM; i++) {
           for (int j = 0; j < DIM; j++) {
               data.push_back(QwtPoint3D(i * sys->step() , j * sys->step(), sys->phi[i][j]));
               }
    }
    curve->setSamples(data);
    plot->replot();
}
