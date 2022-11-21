#pragma once

#include <twinzo/tdevkit/contracts/core.pb.h>
#include <twinzo/tdevkit/contracts/helpers.pb.h>

#include <memory>
#include <string>
#include <twinzo/network/network_client.hpp>

template <class HttpClient>
class tDevkit {
public:
  std::string hostname;
  int port;

  std::string client;
  std::string login;
  std::string password;

  std::string client_guid;
  std::string branch_guid;
  std::string token;
  std::string api_key;

  tDevkit(std::string hostname, int port);
  ~tDevkit();

  /* Areas */
  auto getAreas(const std::vector<NetworkQuery>& query = {})
      -> std::vector<AreaContract>;
  auto getArea(const int& id, const std::vector<NetworkQuery>& query = {})
      -> AreaContract;

  /* Authorization */
  auto setAuthHeaders(
      std::string client_guid, std::string branch_guid, std::string token
  ) -> void;
  auto deleteCurrentToken() -> void;
  auto getToken() -> AuthenticationResponseContract const;
  auto authenticate(const CredentialContract& credentials)
      -> AuthenticationResponseContract const;
  auto authenticate(std::string client, std::string login, std::string password)
      -> AuthenticationResponseContract const;
  auto authenticate() -> AuthenticationResponseContract const;

  /* Configuration */
  auto getBranchConfiguration(const std::string& key) -> std::string;
  auto getAccountConfiguration(const std::string& key) -> std::string;
  auto getAccountConfiguration(const std::string& login, const std::string& key)
      -> std::string;
  auto getConfigurationLastChange(const std::string& key) -> int64_t;

  /* Devices */
  auto getDevices(const std::vector<NetworkQuery>& query = {})
      -> std::vector<DeviceContract>;
  auto getDevice(const int& id, const std::vector<NetworkQuery>& query = {})
      -> DeviceContract;
  auto getDevice(
      const std::string& login, const std::vector<NetworkQuery>& query = {}
  ) -> DeviceContract;
  auto addDevice(const DeviceContract& device) -> DeviceContract;
  auto updateDevice(const DeviceContract& device) -> DeviceContract;
  auto deleteDevice(const int& id) -> void;

  /* Layers */
  auto getLayers(const std::vector<NetworkQuery>& query = {})
      -> std::vector<LayerContract>;
  auto getLayer(const int& id, const std::vector<NetworkQuery>& query = {})
      -> LayerContract;
  auto getNoGoLayers(
      const std::string& login, const std::vector<NetworkQuery>& query = {}
  ) -> std::vector<LayerContract>;
  auto getLocalizationLayers(
      const std::string& login, const std::vector<NetworkQuery>& query = {}
  ) -> std::vector<LayerContract>;
  auto getLocalizationLayers(
      const LoginContract& login, const std::vector<NetworkQuery>& query = {}
  ) -> std::vector<LayerContract>;

  /* Localization */
  auto addLocalizationData(const std::vector<DeviceLocationContract>& locations)
      -> void;
  auto addLocalizationData(const std::vector<LocationContract>& locations)
      -> void;

  /* Sensors */
  auto getSensors(const std::vector<NetworkQuery>& query = {})
      -> std::vector<SensorContract>;
  auto getSensor(const int& id, const std::vector<NetworkQuery>& query = {})
      -> SensorContract;
  auto getSensor(
      const std::string& login, const std::vector<NetworkQuery>& query = {}
  ) -> SensorContract;
  /** Not implemented */
  auto getSensorData(
      const int& id, std::vector<std::string>& quantities, const int64_t& start,
      const int64_t& stop, const std::string& aggregation = "mean"
  ) -> std::vector<SensorDataContract> = delete;
  auto addSensor(const SensorContract& sensor) -> SensorContract;
  /**
   * Not implemented
   * Doesn't work due to issues with partial protobuf deserialization
   * on the server side (Invalid wire-type error)
   */
  auto updateSensor(const SensorContract& sensor) -> void = delete;
  auto deleteSensor(const int& id) -> void;
  auto addSensorData(const std::vector<SensorBatchContract>& batch_data)
      -> void;
  auto addSensorData(const std::vector<SensorDataBatchContract>& sensor_data)
      -> void;
  auto getSensorAppInfo() -> SensorAppInfoContract;
  /** Not implemented */
  auto getSensorAppFile() -> void = delete;

protected:
  template <class Contract, class PayloadContract>
  auto serviceRequest(
      NetworkMethod method, std::string path, PayloadContract data,
      const std::vector<NetworkHeader>& headers = {},
      const std::vector<NetworkQuery>& query    = {},
      const std::string& content_type           = "application/x-protobuf"
  ) -> Contract;

private:
  std::unique_ptr<HttpClient> m_network_client;
};

// Main implementation
#include <twinzo/tdevkit/tdevkit.tpp>
// Functionality implementations
#include <twinzo/tdevkit/areas.tpp>
#include <twinzo/tdevkit/authorization.tpp>
#include <twinzo/tdevkit/configuration.tpp>
#include <twinzo/tdevkit/devices.tpp>
#include <twinzo/tdevkit/layers.tpp>
#include <twinzo/tdevkit/sensors.tpp>