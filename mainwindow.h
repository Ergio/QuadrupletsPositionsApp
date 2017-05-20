#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QProgressDialog>
#include <QtCharts/QChartView>
#include "ncbidownloaddialog.h"
#include "codondensityplot.h"
#include "CodonCount/plot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	void replotCodonsPlot();
	~MainWindow();

private slots:
	void on_open_gemone_file_button_clicked();
	void on_ncbi_download_button_clicked();
	void updateDownloadProgress(qint64, qint64);

	void on_comboBox_currentIndexChanged(int);

	void on_horizontalSlider_valueChanged(int value);

	void on_checkBox_quadruplets_clicked(bool checked);

private:
	bool countQuadruplets;
	bool useSpline;
	int amountOfPoints = 50; // by default
	int codonIndex;

	CodonDensityPlot* codonPlot;
	QChartView* codonPlotView;
	QString* selectedGenomeStr = new QString();
	Ui::MainWindow *ui;
	NCBIDownloadDialog* ncbiDownloadDialog;
	QProgressDialog *progressDialog;
};

#endif // MAINWINDOW_H
