/*
  Test of DELAYED GET reqest with Qt client
  - Generates random integer as query items
  - sets delay time of 5 seconds
  - Returns query items in payload
  - Tests if no data corruption occurred 
*/

#include <twinzo/network/qt_client.hpp>

#include <ctype.h>
#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QRandomGenerator>

std::string host = "https://httpbin.org";
std::string path = "/delay/2";

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
  request.query_items.push_back(NetworkQuery("testQueryItem", std::to_string(queryTest)));

  if(argc > 1 && atoi(argv[1]))
    client.timeout(atoi(argv[1]));

  client.connect();

  NetworkResponse response = client.get(request);
  QJsonDocument outDoc = QJsonDocument::fromJson(
    QByteArray(response.payload.c_str(), response.payload.size())
  );
  QJsonObject outObj = outDoc.object();
  QJsonObject outArgs = outObj["args"].toObject();
  int outVal = outArgs["testQueryItem"].toString().toInt();

  // Assert
  if (outVal != queryTest)
    return 1;

  queryTest = QRandomGenerator::global()->generate() % 1000;
  request.query_items.clear();
  request.query_items.push_back(NetworkQuery("testQueryItem", std::to_string(queryTest)));

  response = client.request(NetworkMethod::Get, request);
  outDoc = QJsonDocument::fromJson(
    QByteArray(response.payload.c_str(), response.payload.size())
  );
  outObj = outDoc.object();
  outArgs = outObj["args"].toObject();
  outVal = outArgs["testQueryItem"].toString().toInt();

  // Assert
  if (outVal != queryTest)
    return 1;

  return 0;
}