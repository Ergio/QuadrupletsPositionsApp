#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ncbifetcher.h"
#include "CodonCount/plot.h"
#include "algorithm"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);
	ui->verticalLayout->setAlignment(Qt::AlignTop);

	codonPlot = new CodonDensityPlot;
	codonPlotView = new QChartView(codonPlot,this);
	ui->horizontalLayout->addWidget(codonPlotView);

	codonPlot->setAnimationOptions(QChart::AllAnimations);
	codonPlotView->setRenderHint(QPainter::Antialiasing);

	QStringList codonsList;
	for (auto& codon:codons) {
		codonsList.append(QString::fromStdString(codon));
	}
	ui->comboBox->addItems(codonsList);
	ui->comboBox->setCurrentIndex(-1);

}

void MainWindow::replotCodonsPlot() {

	codonPlot->removeAllSeries();

	if (codonIndex < 0 || codonIndex >= 64) return;

	std::string str1 = selectedGenomeStr->toStdString();
	Genome strept(str1);

	if (!countQuadruplets) {

		std::vector<double> codon_data = strept.CodonsPositionsOne(codonIndex);
		std::vector< std::pair<double,double> > plot = CalcDensity(codon_data,amountOfPoints);

		QSplineSeries *series = new QSplineSeries;

		series->setName(QString::fromStdString(codons[codonIndex]));

		for (auto& i:plot) {
			series->append(i.second,i.first);
		}

		codonPlot->addSeries(series);
	} else {

		std::vector<int> quadrupletsIndexes = getQuadrsByCodon(codonIndex);

		for (auto& index:quadrupletsIndexes) {
			std::vector<double> codon_data = strept.QuadrupletsPositionsOne(index);
			std::vector< std::pair<double,double> > plot = CalcDensity(codon_data,amountOfPoints);

			QSplineSeries *series = new QSplineSeries;

			series->setName(QString::fromStdString(quadrs[index]));

			for (auto& i:plot) {
				series->append(i.second,i.first);
			}

			codonPlot->addSeries(series);
		}
	}

//	QLineSeries *series1 = new QLineSeries;

//	series1->setName(QString::fromStdString(codons[codonIndex]));

//	for (auto& i:plot) {
//		series1->append(i.second,i.first);
//	}

//	codonPlot->addSeries(series1);
}

MainWindow::~MainWindow() {

	delete codonPlot;
	delete selectedGenomeStr;
	delete ui;
}

void MainWindow::on_open_gemone_file_button_clicked() {
	/*	String containing chosed file path + file name	*/
	QString genome_file_name;
	genome_file_name = QFileDialog::getOpenFileName(
				this,"Open genome file",QDir::currentPath());

	if (!genome_file_name.isEmpty()) {
		QFile genomeFile(genome_file_name);
		genomeFile.open(QIODevice::ReadOnly);
		//delete selectedGenomeStr;
        selectedGenomeStr = new QString(genomeFile.readAll());
        genomeFile.close();
	}

}

void MainWindow::on_ncbi_download_button_clicked() {
	ncbiDownloadDialog = new NCBIDownloadDialog(this);



	ncbiDownloadDialog->show();

	if (ncbiDownloadDialog->exec() == QDialog::Accepted) {
		/*	corynebacterium efficiens	*/

		const QString& speciesName = ncbiDownloadDialog->getSpecies();

		NCBIFetcher* ncbiFetcher = new NCBIFetcher(this);

		progressDialog = new QProgressDialog;
		progressDialog->setWindowTitle(QString("Donwloading for %1...").arg(speciesName));
		progressDialog->setWindowModality(Qt::ApplicationModal);
		progressDialog->setMinimumDuration(0);

		connect(progressDialog,SIGNAL(canceled()),ncbiFetcher,SIGNAL(abort()));
		connect(progressDialog,SIGNAL(canceled()),progressDialog,SLOT(deleteLater()));
		connect(ncbiFetcher,SIGNAL(genomeDownloaded()),progressDialog,SLOT(deleteLater()));
		connect(ncbiFetcher,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(updateDownloadProgress(qint64,qint64)));

		QApplication::processEvents();

		QString downloadedGenome;

		try {
			downloadedGenome = ncbiFetcher->fetch(speciesName);
		} catch (const QString& msg) {
			//qDebug() << msg;
			emit progressDialog->canceled();
			QMessageBox(QMessageBox::Warning,"Error...",msg,QMessageBox::Ok).exec();
		}

		qDebug() << downloadedGenome;

	}
}

void MainWindow::updateDownloadProgress(qint64 received, qint64 total) {
	progressDialog->setMinimum(0);
	progressDialog->setMaximum(total>0?total:-total);
	progressDialog->setValue(received);

	QString mul = "Bytes";

	if (received > 1024*1024) {
		received /= 1024*1024;
		total /= 1024*1024;
		mul = "MBytes";
	} else if (received > 1024) {
		received /= 1024;
		total /= 1024;
		mul = "KBytes";
	}

	if (total > 0)
		progressDialog->setLabelText(QString("Downloading %1 %3/%2 %3...").arg(
										 QString::number(received),QString::number(total),mul));
	else
		progressDialog->setLabelText(QString("Downloading %1 %3/%2 %3...").arg(
										 QString::number(received),"unknown",mul));
}


void MainWindow::on_comboBox_currentIndexChanged(int cIndex) {
	codonIndex = cIndex;
	replotCodonsPlot();
}

void MainWindow::on_horizontalSlider_valueChanged(int value) {
	amountOfPoints = value;
	replotCodonsPlot();
}
void MainWindow::on_checkBox_quadruplets_clicked(bool checked) {
	countQuadruplets = checked;
	replotCodonsPlot();
}
