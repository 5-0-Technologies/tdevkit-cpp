#include <twinzo/tdevkit/tdevkit.hpp>

template <class HttpClient>
auto tDevkit<HttpClient>::getSensors(const std::vector<NetworkQuery>& query)
    -> std::vector<SensorContract> {
  auto response = this->serviceRequest<SensorContractList, void*>(
      NetworkMethod::Get, "/api/v3/sensors", nullptr, {}, query
  );

  // Deserialize the repeating field into a vector
  return std::vector<SensorContract>(
      response.contracts().begin(), response.contracts().end()
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::getSensor(
    const int& id, const std::vector<NetworkQuery>& query
) -> SensorContract {
  return this->serviceRequest<SensorContract, void*>(
      NetworkMethod::Get, "/api/v3/sensors/" + std::to_string(id), nullptr, {},
      query
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::getSensor(
    const std::string& login, const std::vector<NetworkQuery>& query
) -> SensorContract {
  return this->serviceRequest<SensorContract, void*>(
      NetworkMethod::Get, "/api/v3/sensors/login/" + login, nullptr, {}, query
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::addSensor(const SensorContract& sensor)
    -> SensorContract {
  return this->serviceRequest<SensorContract, SensorContract>(
      NetworkMethod::Post, "/api/v3/sensors", sensor
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::deleteSensor(const int& id) -> void {
  return this->serviceRequest<void, void*>(
      NetworkMethod::Delete, "/api/v3/sensors/" + std::to_string(id), nullptr
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::addSensorData(
    const std::vector<SensorBatchContract>& data
) -> void {
  SensorBatchContractList contract;
  contract.mutable_contracts()->Assign(data.begin(), data.end());

  return this->serviceRequest<void, SensorBatchContractList>(
      NetworkMethod::Post, "/api/v3/sensors/batch", contract
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::addSensorData(
    const std::vector<SensorDataBatchContract>& batch_data
) -> void {
  SensorDataBatchContractList contract;
  contract.mutable_contracts()->Assign(batch_data.begin(), batch_data.end());

  return this->serviceRequest<void, SensorDataBatchContractList>(
      NetworkMethod::Post, "/api/v3/sensors/sensor-data", contract
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::getSensorAppInfo() -> SensorAppInfoContract {
  return this->serviceRequest<SensorAppInfoContract, void*>(
      NetworkMethod::Get, "/api/v3/sensors/app-info", nullptr
  );
}