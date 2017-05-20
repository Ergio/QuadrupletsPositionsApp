#ifndef NCBIFETCHER_H
#define NCBIFETCHER_H

#include <QObject>
#include <QList>
#include <QEventLoop>
#include "downloader.h"

class NCBIFetcher : public QObject
{
	Q_OBJECT
public:

	enum State {Nothing,Searching,Linking,Fetching};

	explicit NCBIFetcher(QObject *parent = nullptr);

	QString fetch(const QString &);

signals:
	void abort();
	void done();
	void genomeDownloaded();
	void downloadProgress(qint64,qint64);

private slots:

	void finished(QNetworkReply*);

private:

	QString findSpeciesID(const QString&);
	QPair<QString,QString> findWebEnvbyId(const QString &);
	void downloadGenome(const QPair<QString, QString>&);


	QStringList parseOut(const QString&);

private:
	const QString baseUrl = "https://eutils.ncbi.nlm.nih.gov/entrez/eutils/";
	const QString searchScript = "esearch.fcgi";
	const QString linkScript = "elink.fcgi";
	const QString fetchScript = "efetch.fcgi";

	State state;

	QString recentData;

	QEventLoop loop;
	Downloader* downloader;
	QUrl url;
	QUrlQuery urlQuery;
};

#endif // NCBIFETCHER_H
