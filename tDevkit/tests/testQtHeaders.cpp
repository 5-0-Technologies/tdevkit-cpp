/*
  Test of HEADERS with Qt client
  - Generates random integer as header item
  - Returns header in response headers
  - Tests if no data corruption occurred 
*/

#include <qtNetworkClient.hpp>

#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QRandomGenerator>

std::string host = "https://httpbin.org";
std::string path = "/headers";

int main(int argc, char *argv[])
{
  qputenv("QT_QPA_PLATFORM", "offscreen");
  QApplication app(argc, argv);

  QtNetworkClient client(host, 80);

  int headerTest = QRandomGenerator::global()->generate() % 1000;
  
  NetworkRequest request;
  request.url = path;
  request.headers.push_back(NetworkHeader("Test-Header-Item", std::to_string(headerTest)));
  
  client.connect();

  NetworkResponse response = client.get(request);
  QJsonDocument outDoc = QJsonDocument::fromJson(QByteArray(reinterpret_cast<const char*>(response.payload.data()), response.payload.size()));
  QJsonObject outObj = outDoc.object();
  QJsonObject outHeaders = outObj["headers"].toObject();
  int outVal = outHeaders["Test-Header-Item"].toString().toInt();
  assert(outVal == headerTest);

  headerTest = QRandomGenerator::global()->generate() % 1000;
  request.headers.clear();
  request.headers.push_back(NetworkHeader("Test-Header-Item", std::to_string(headerTest)));

  response = client.request(NetworkMethod::Get, request);
  outDoc = QJsonDocument::fromJson(QByteArray(reinterpret_cast<const char*>(response.payload.data()), response.payload.size()));
  outObj = outDoc.object();
  outHeaders = outObj["headers"].toObject();
  outVal = outHeaders["Test-Header-Item"].toString().toInt();
  assert(outVal == headerTest);

  return 0;
}