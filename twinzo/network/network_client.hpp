#pragma once

#include <string>
#include <tuple>
#include <vector>

enum class NetworkMethod {
  Get     = 1,
  Head    = 2,
  Post    = 3,
  Put     = 4,
  Delete  = 5,
  Connect = 6,
  Options = 7,
  Trace   = 8,
  Patch   = 9,
};

using HttpVersion = std::tuple<int, int>;
using NetworkHeader = std::pair<std::string, std::string>;
using NetworkQuery = std::pair<std::string, std::string>;
using NetworkPayload = std::string;

struct NetworkResponse {
  int status_code;
  std::string status_line;
  std::vector<NetworkHeader> headers;
  HttpVersion http_version;
  NetworkPayload payload;
};

struct NetworkRequest {
  std::string url;
  std::vector<NetworkHeader> headers;
  std::vector<NetworkQuery> query_items;
};

class NetworkClient {
protected:
  std::string m_hostname;
  int m_port;

  NetworkClient(std::string hostname, int port) {
    m_hostname = hostname;
    m_port = port;
  };
  virtual ~NetworkClient() {};

  virtual auto connect() -> void = 0;
  virtual auto disconnect() -> void = 0;
  virtual auto timeout(int) -> void = 0;
  virtual auto timeout() -> const int = 0;
  virtual auto request(
      NetworkMethod, NetworkRequest&, NetworkPayload* = nullptr
  ) -> NetworkResponse = 0;

  virtual auto head(NetworkRequest&) -> NetworkResponse = 0;
  virtual auto get(NetworkRequest&) -> NetworkResponse = 0;
  virtual auto put(NetworkRequest&, NetworkPayload*) -> NetworkResponse = 0;
  virtual auto post(NetworkRequest&, NetworkPayload*) -> NetworkResponse = 0;
  virtual auto patch(NetworkRequest&, NetworkPayload*) -> NetworkResponse = 0;
  virtual auto trace(NetworkRequest&) -> NetworkResponse = 0;
  virtual auto options(NetworkRequest&) -> NetworkResponse = 0;
  virtual auto connect(NetworkRequest&) -> NetworkResponse = 0;
  virtual auto deleteResource(NetworkRequest&) -> NetworkResponse = 0;
};
