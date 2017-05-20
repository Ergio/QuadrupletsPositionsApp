#include "ncbidownloaddialog.h"
#include "ui_ncbidownloaddialog.h"

NCBIDownloadDialog::NCBIDownloadDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NCBIDownloadDialog) {
	ui->setupUi(this);
}

QString NCBIDownloadDialog::getSpecies() const {
	return ui->speciesName->text();
}

NCBIDownloadDialog::~NCBIDownloadDialog() {
	delete ui;
}
