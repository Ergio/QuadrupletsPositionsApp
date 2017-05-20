#include "codondensityplot.h"

#include <QDebug>

CodonDensityPlot::CodonDensityPlot(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
	QChart(QChart::ChartTypeCartesian,parent,wFlags) {

	this->setTitle(titleName);
	this->setTitleFont(defaultTitleFont);
	this->legend()->setFont(defaultLegendFont);
	this->legend()->setColor(defaultLegendColor);
	this->setBackgroundBrush(QBrush(defaultBackgroundColor));
}

void CodonDensityPlot::addSeries(QAbstractSeries *series) {
	QChart::addSeries(series);
	this->createDefaultAxes();
	this->axes().operator [](0)->setTitleText(xAxisName);
	this->axes().operator [](1)->setTitleText(yAxisName);
}

CodonDensityPlot::~CodonDensityPlot() {

}
