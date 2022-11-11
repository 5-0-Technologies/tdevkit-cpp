#include <twinzo/tdevkit/tdevkit.hpp>

template <class HttpClient>
auto tDevkit<HttpClient>::getDevices(const std::vector<NetworkQuery> &query)
    -> std::vector<DeviceContract> {
  auto response = this->serviceRequest<DeviceContractList, void *>(
      NetworkMethod::Get, "/api/v3/devices", nullptr,
      std::vector<NetworkHeader>(), query
  );

  // Deserialize the repeating field into a vector
  return std::vector<DeviceContract>(
      response.contracts().begin(), response.contracts().end()
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::getDevice(
    const int &id, const std::vector<NetworkQuery> &query
) -> DeviceContract {
  return this->serviceRequest<DeviceContract, void *>(
      NetworkMethod::Get, "/api/v3/devices/" + std::to_string(id), nullptr,
      std::vector<NetworkHeader>(), query
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::getDevice(
    const std::string &login, const std::vector<NetworkQuery> &query
) -> DeviceContract {
  return this->serviceRequest<DeviceContract, void *>(
      NetworkMethod::Get, "/api/v3/devices/login/" + login, nullptr,
      std::vector<NetworkHeader>(), query
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::addDevice(const DeviceContract &device)
    -> DeviceContract {
  return this->serviceRequest<DeviceContract, DeviceContract>(
      NetworkMethod::Post, "/api/v3/devices", device
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::updateDevice(const DeviceContract &device)
    -> DeviceContract {
  return this->serviceRequest<DeviceContract, DeviceContract>(
      NetworkMethod::Patch, "/api/v3/devices/" + std::to_string(device.id()),
      device
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::deleteDevice(const int &id) -> void {
  this->serviceRequest<void, void *>(
      NetworkMethod::Delete, "/api/v3/devices/" + std::to_string(id), nullptr
  );
}