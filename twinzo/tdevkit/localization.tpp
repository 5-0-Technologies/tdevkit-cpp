#include <twinzo/tdevkit/tdevkit.hpp>

template <class HttpClient>
auto tDevkit<HttpClient>::addLocalizationData(
    const std::vector<DeviceLocationContract>& locations
) -> void {
  DeviceLocationContractList contract;
  contract.mutable_contracts()->Add(locations.begin(), locations.end());

  this->serviceRequest<void, DeviceLocationContractList>(
      NetworkMethod::Post, "/api/v3/localization/batch", contract
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::addLocalizationData(
    const std::vector<LocationContract>& locations
) -> void {
  LocationContractList contract;
  contract.mutable_contracts()->Add(locations.begin(), locations.end());

  this->serviceRequest<void, LocationContractList>(
      NetworkMethod::Post, "/api/v3/localization", contract
  );
}