/*
  Test of POST reqest with Qt client
  - Generates random integer as payload
  - Returns payload in response payload
  - Tests if no data corruption occurred 
*/

#include <qtNetworkClient.hpp>

#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QRandomGenerator>

std::string host = "https://httpbin.org";
std::string path = "/post";

int main(int argc, char *argv[])
{
  qputenv("QT_QPA_PLATFORM", "offscreen");
  QApplication app(argc, argv);

  QtNetworkClient client(host, 80);

  NetworkRequest request;
  request.url = path;
  request.headers.push_back(NetworkHeader("Content-Type", "application/json"));
  request.headers.push_back(NetworkHeader("Accept", "application/json"));

  int queryTest = QRandomGenerator::global()->generate() % 1000;

  QJsonObject obj;
  obj["testQueryItem"] = QString::number(queryTest);
  QJsonDocument doc(obj);
  QByteArray payload = doc.toJson();
  
  client.connect();
  NetworkResponse response = client.post(request, new NetworkPayload(payload.begin(), payload.end()));

  QJsonDocument outDoc = QJsonDocument::fromJson(QByteArray(reinterpret_cast<const char*>(response.payload.data()), response.payload.size()));
  QJsonObject outObj = outDoc.object();
  QJsonObject outArgs = QJsonDocument::fromJson(outObj["data"].toString().toUtf8()).object();
  int outVal = outArgs["testQueryItem"].toString().toInt();
  assert(outVal == queryTest);

  queryTest = QRandomGenerator::global()->generate() % 1000;
  obj["testQueryItem"] = QString::number(queryTest);
  doc = QJsonDocument(obj);
  payload = doc.toJson();

  response = client.request(NetworkMethod::Post, request, new NetworkPayload(payload.begin(), payload.end()));
  outDoc = QJsonDocument::fromJson(QByteArray(reinterpret_cast<const char*>(response.payload.data()), response.payload.size()));
  outObj = outDoc.object();
  outArgs = QJsonDocument::fromJson(outObj["data"].toString().toUtf8()).object();
  outVal = outArgs["testQueryItem"].toString().toInt();
  assert(outVal == queryTest);

  return 0;
}