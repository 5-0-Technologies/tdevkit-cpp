#include <twinzo/tdevkit/tdevkit.hpp>

template <class HttpClient>
auto tDevkit<HttpClient>::getLayers(const std::vector<NetworkQuery> &query)
    -> std::vector<LayerContract> {
  auto response = this->serviceRequest<LayerContractList, void *>(
      NetworkMethod::Get, "/api/v3/layers", nullptr,
      std::vector<NetworkHeader>(), query
  );

  // Deserialize the repeating field into a vector
  return std::vector<LayerContract>(
      response.contracts().begin(), response.contracts().end()
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::getLayer(
    const int &id, const std::vector<NetworkQuery> &query
) -> LayerContract {
  return this->serviceRequest<LayerContract, void *>(
      NetworkMethod::Get, "/api/v3/layers/" + std::to_string(id), nullptr,
      std::vector<NetworkHeader>(), query
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::getNoGoLayers(
    const std::string &login, const std::vector<NetworkQuery> &query
) -> std::vector<LayerContract> {
  auto response = this->serviceRequest<LayerContractList, void *>(
      NetworkMethod::Get, "/api/v3/layers/device/" + login, nullptr,
      std::vector<NetworkHeader>(), query
  );

  // Deserialize the repeating field into a vector
  return std::vector<LayerContract>(
      response.contracts().begin(), response.contracts().end()
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::getLocalizationLayers(
    const std::string &login, const std::vector<NetworkQuery> &query
) -> std::vector<LayerContract> {
  auto response = this->serviceRequest<LayerContractList, void *>(
      NetworkMethod::Get, "/api/v3/layers/localization/" + login, nullptr,
      std::vector<NetworkHeader>(), query
  );

  // Deserialize the repeating field into a vector
  return std::vector<LayerContract>(
      response.contracts().begin(), response.contracts().end()
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::getLocalizationLayers(
    const LoginContract &login, const std::vector<NetworkQuery> &query
) -> std::vector<LayerContract> {
  auto response = this->serviceRequest<LayerContractList, LoginContract>(
      NetworkMethod::Post, "/api/v3/layers/localization", login,
      std::vector<NetworkHeader>(), query
  );

  // Deserialize the repeating field into a vector
  return std::vector<LayerContract>(
      response.contracts().begin(), response.contracts().end()
  );
}