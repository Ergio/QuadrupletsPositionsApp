#ifndef NCBIDOWNLOADDIALOG_H
#define NCBIDOWNLOADDIALOG_H

#include <QDialog>
#include <QMessageBox>


namespace Ui {
class NCBIDownloadDialog;
}

class NCBIDownloadDialog : public QDialog
{
	Q_OBJECT

public:
	explicit NCBIDownloadDialog(QWidget *parent = nullptr);
	QString getSpecies() const;
	~NCBIDownloadDialog();

private:
	Ui::NCBIDownloadDialog *ui;
};

#endif // NCBIDOWNLOADDIALOG_H
