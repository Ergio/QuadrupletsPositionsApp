#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

/*	Downloader class. Implements async downloading	*/
class Downloader : public QObject
{
	Q_OBJECT
public:
	explicit Downloader(QObject *parent = nullptr);
	void sendRequest(const QUrl&);
signals:
	void downloadProgress(qint64,qint64);
	void cancel();
	void finished(QNetworkReply*);


private:
	QNetworkAccessManager* qnam;
};

#endif // DOWNLOADER_H
