#ifndef CODONDENSITYPLOT_H
#define CODONDENSITYPLOT_H

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>

#include <vector>

QT_CHARTS_USE_NAMESPACE


class CodonDensityPlot : public QChart
{
	Q_OBJECT
public:
	CodonDensityPlot(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
	void addSeries(QAbstractSeries*);
	virtual ~CodonDensityPlot();

private:
	/*	title name	*/
	const QString titleName = "Codon density vs rel. position";
	/*	defualt font for title text	*/
	const QFont defaultTitleFont = QFont("sans", 12, QFont::Bold);
	/*	Axis names	*/
	const QString xAxisName = "Relative intragenic position";
	const QString yAxisName = "Count";
	/*	Sans font for legend text	*/
	const QFont defaultLegendFont = QFont("Helvetica [Cronyx]", 9);
	/*	White color for legend background	*/
	const QColor defaultLegendColor = QColor(255,255,255);
	/*	White color for legend background	*/
	const QColor defaultBackgroundColor = QColor(255,255,255);
};

#endif // CODONDENSITYPLOT_H
