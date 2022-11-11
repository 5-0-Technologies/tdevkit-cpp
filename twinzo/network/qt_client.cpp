#include <QBuffer>
#include <twinzo/network/exceptions.hpp>
#include <twinzo/network/qt_client.hpp>

#include <iostream>

QtNetworkClient::QtNetworkClient(std::string hostname, int port)
    : NetworkClient(hostname, port) {
  m_manager = new QNetworkAccessManager();
}

QtNetworkClient::~QtNetworkClient() {}

void QtNetworkClient::connect() {
  m_manager->connectToHost(QString::fromStdString(m_hostname), m_port);
}

void QtNetworkClient::disconnect() {}

void QtNetworkClient::timeout(int timeout) {
  m_manager->setTransferTimeout(timeout);
}

const int QtNetworkClient::timeout() {
  return m_manager->transferTimeout();
}

NetworkResponse QtNetworkClient::request(
    NetworkMethod method, NetworkRequest& request, NetworkPayload* payload
) {
  QUrlQuery query;
  for (auto q : request.query_items) {
    query.addQueryItem(QString(q.first.c_str()), QString(q.second.c_str()));
  }

  QUrl url(QString::fromStdString(m_hostname + request.url));
  url.setQuery(query);
  QNetworkRequest qRequest(url);
  for (auto header : request.headers)
    qRequest.setRawHeader(
        QByteArray(header.first.c_str(), header.first.length()),
        QByteArray(header.second.c_str(), header.second.length())
    );

  // Copy data to QBuffer (QIODevice) if any is available
  std::unique_ptr<QBuffer> data;
  if (payload != nullptr) {
    data = std::make_unique<QBuffer>();
    data->setData(payload->c_str(), payload->size());
  }

  auto reply = m_manager->sendCustomRequest(
      qRequest, methodMap.at(method).toUtf8(), data.get()
  );

  // Synchronously wait for the network reply
  QEventLoop requestLoop;
  QObject::connect(
      reply, &QNetworkReply::finished, &requestLoop, &QEventLoop::quit
  );
  requestLoop.exec();

  reply->deleteLater();

  auto reply_err = reply->error();
  if (reply_err == QNetworkReply::NoError) {
    return parseQtResponse(reply);
  } else {
    std::cout << reply->readAll().toStdString() << std::endl;
    throw NetworkException(reply_err, reply->errorString().toStdString());
  }
}

NetworkResponse QtNetworkClient::head(NetworkRequest& request) {
  return this->request(NetworkMethod::Head, request);
}

NetworkResponse QtNetworkClient::get(NetworkRequest& request) {
  return this->request(NetworkMethod::Get, request);
}

NetworkResponse QtNetworkClient::put(
    NetworkRequest& request, NetworkPayload* payload
) {
  return this->request(NetworkMethod::Put, request, payload);
}

NetworkResponse QtNetworkClient::post(
    NetworkRequest& request, NetworkPayload* payload
) {
  return this->request(NetworkMethod::Post, request, payload);
}

NetworkResponse QtNetworkClient::deleteResource(NetworkRequest& request) {
  return this->request(NetworkMethod::Delete, request);
}

NetworkResponse QtNetworkClient::patch(
    NetworkRequest& request, NetworkPayload* payload
) {
  return this->request(NetworkMethod::Patch, request, payload);
}

NetworkResponse QtNetworkClient::options(NetworkRequest& request) {
  return this->request(NetworkMethod::Options, request);
}

NetworkResponse QtNetworkClient::connect(NetworkRequest& request) {
  return this->request(NetworkMethod::Connect, request);
}

NetworkResponse QtNetworkClient::trace(NetworkRequest& request) {
  return this->request(NetworkMethod::Trace, request);
}

NetworkResponse QtNetworkClient::parseQtResponse(QNetworkReply* reply) {
  NetworkResponse response;
  response.status_code =
      reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
  response.status_line =
      reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute)
          .toString()
          .toStdString();
  response.http_version = HttpVersion(1, 1);
  for (auto headerPair : reply->rawHeaderPairs()) {
    response.headers.push_back(NetworkHeader(
        std::string(headerPair.first.constData(), headerPair.first.length()),
        std::string(headerPair.second.constData(), headerPair.second.length())
    ));
  }

  response.payload = reply->readAll().toStdString();

  return response;
}
