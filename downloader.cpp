#include "downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent) {
	qnam = new QNetworkAccessManager(this);
	connect(qnam,SIGNAL(finished(QNetworkReply*)),this,SIGNAL(finished(QNetworkReply*)));
}

void Downloader::sendRequest(const QUrl &url) {
	QNetworkRequest request(url);
	QNetworkReply *reply = qnam->get(request);
	connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SIGNAL(downloadProgress(qint64,qint64)));
	connect(this,SIGNAL(cancel()),reply,SLOT(abort()));
}
