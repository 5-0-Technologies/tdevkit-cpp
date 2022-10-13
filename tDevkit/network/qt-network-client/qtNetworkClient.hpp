#include <map>

#include <NetworkClient.hpp>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QString>
#include <QEventLoop>
#include <QUrlQuery>

static std::map<NetworkMethod, QString> methodMap = {
    {NetworkMethod::Get, "GET"},
    {NetworkMethod::Head, "HEAT"},
    {NetworkMethod::Post, "POST"},
    {NetworkMethod::Put, "PUT"},
    {NetworkMethod::Delete, "DELETE"},
    {NetworkMethod::Connect, "CONNECT"},
    {NetworkMethod::Options, "OPTIONS"},
    {NetworkMethod::Trace, "TRACE"},
    {NetworkMethod::Patch, "PATCH"}
};

class QtNetworkClient : public QObject, public NetworkClient {
  Q_OBJECT
private:
  QNetworkAccessManager *m_manager;
  NetworkResponse parseQtResponse(QNetworkReply *);

public:
  QtNetworkClient(std::string hostname, int port);
  ~QtNetworkClient();

  auto connect() -> void;
  auto disconnect() -> void;
  auto timeout(int) -> void;
  auto timeout() -> const int;
  auto request(NetworkMethod, NetworkRequest&, NetworkPayload* = nullptr)
      -> NetworkResponse;

  auto head(NetworkRequest&) -> NetworkResponse;
  auto get(NetworkRequest&) -> NetworkResponse;
  auto put(NetworkRequest&, NetworkPayload*) -> NetworkResponse;
  auto post(NetworkRequest&, NetworkPayload*) -> NetworkResponse;
  auto patch(NetworkRequest&, NetworkPayload*) -> NetworkResponse;
  auto trace(NetworkRequest&) -> NetworkResponse;
  auto options(NetworkRequest&) -> NetworkResponse;
  auto connect(NetworkRequest&) -> NetworkResponse;
  auto deleteResource(NetworkRequest&) -> NetworkResponse;
};
