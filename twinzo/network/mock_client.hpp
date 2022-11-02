#include <string>
#include <twinzo/network/network_client.hpp>

class MockNetworkClient : protected NetworkClient {
public:
  MockNetworkClient(std::string hostname, int port)
      : NetworkClient(hostname, port) {}
  ~MockNetworkClient() {}

  auto connect() -> void {}
  auto disconnect() -> void {}
  auto timeout(int timeout) -> void {}
  auto timeout() -> const int {
    return 0;
  }

  auto request(NetworkMethod, NetworkRequest&, NetworkPayload*)
      -> NetworkResponse {
    return NetworkResponse();
  }

  auto head(NetworkRequest&) -> NetworkResponse {
    return NetworkResponse();
  }
  auto get(NetworkRequest&) -> NetworkResponse {
    return NetworkResponse();
  }
  auto put(NetworkRequest&, NetworkPayload*) -> NetworkResponse {
    return NetworkResponse();
  }
  auto post(NetworkRequest&, NetworkPayload*) -> NetworkResponse {
    return NetworkResponse();
  }
  auto patch(NetworkRequest&, NetworkPayload*) -> NetworkResponse {
    return NetworkResponse();
  }
  auto trace(NetworkRequest&) -> NetworkResponse {
    return NetworkResponse();
  }
  auto options(NetworkRequest&) -> NetworkResponse {
    return NetworkResponse();
  }
  auto connect(NetworkRequest&) -> NetworkResponse {
    return NetworkResponse();
  }
  auto deleteResource(NetworkRequest&) -> NetworkResponse {
    return NetworkResponse();
  }
};
