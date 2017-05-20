#include "ncbifetcher.h"

NCBIFetcher::NCBIFetcher(QObject *parent) : QObject(parent) {
	downloader = new Downloader(this);
	state = Nothing;
	connect(downloader,SIGNAL(finished(QNetworkReply*)),this,SLOT(finished(QNetworkReply*)));
	connect(downloader,SIGNAL(downloadProgress(qint64,qint64)),this,SIGNAL(downloadProgress(qint64,qint64)));
	connect(this,SIGNAL(done()),&loop,SLOT(quit()));
	connect(this,SIGNAL(abort()),&loop,SLOT(quit()));
	connect(this,SIGNAL(abort()),downloader,SIGNAL(cancel()));
}

QString NCBIFetcher::fetch(const QString& name) {
	QString id = findSpeciesID(name);
	auto param = findWebEnvbyId(id);
	downloadGenome(param);

	return recentData;
}

void NCBIFetcher::finished(QNetworkReply * reply) {
	emit done();

	if (reply->error())
		throw QString(reply->errorString());

	if (reply->isOpen())
		recentData = QString(reply->readAll());
}

QString NCBIFetcher::findSpeciesID(const QString & speciesName) {

	state = Searching;

	QList<QPair<QString,QString>> queryItems;
	queryItems.append(QPair<QString,QString>("db","genome"));
	queryItems.append(QPair<QString,QString>("term",speciesName));
	queryItems.append(QPair<QString,QString>("retmax","10000"));
	urlQuery.setQueryItems(queryItems);
	url.setUrl(baseUrl+searchScript);
	url.setQuery(urlQuery);
	downloader->sendRequest(url);
	loop.exec();

	return parseOut("Id")[0];

}

QPair<QString,QString> NCBIFetcher::findWebEnvbyId(const QString& id) {

	state = Linking;

	QList<QPair<QString,QString>> queryItems;
	queryItems.append(QPair<QString,QString>("dbfrom","genome"));
	queryItems.append(QPair<QString,QString>("db","nuccore"));
	queryItems.append(QPair<QString,QString>("id",id));
	queryItems.append(QPair<QString,QString>("cmd","neighbor_history"));

	urlQuery.setQueryItems(queryItems);
	url.setUrl(baseUrl+linkScript);
	url.setQuery(urlQuery);

	downloader->sendRequest(url);

	loop.exec();

	emit genomeDownloaded();

	return QPair<QString,QString>(parseOut("QueryKey")[0],
			parseOut("WebEnv")[0]);
}

void NCBIFetcher::downloadGenome(const QPair<QString, QString> & param) {\

	state = Fetching;

	QList<QPair<QString,QString>> queryItems;
	queryItems.append(QPair<QString,QString>("db","nuccore"));
	queryItems.append(QPair<QString,QString>("query_key",param.first));
	queryItems.append(QPair<QString,QString>("WebEnv",param.second));
	queryItems.append(QPair<QString,QString>("rettype","fasta_cds_na"));
	queryItems.append(QPair<QString,QString>("retmode","text"));

	urlQuery.setQueryItems(queryItems);
	url.setUrl(baseUrl+fetchScript);
	url.setQuery(urlQuery);

	downloader->sendRequest(url);

	loop.exec();
}

QStringList NCBIFetcher::parseOut(const QString& tag) {

	QStringList strList;
	QRegExp re(QString("<%1>(.*)</%1>").arg(tag));

	int last_pos = 0;
	while ((last_pos = re.indexIn(recentData,last_pos)) != -1) {
		last_pos += re.matchedLength();

		strList << re.cap(1);
	}
	if (strList.empty()) {

		throw QString("Error while parsing xml...");
	}

	return strList;
}




