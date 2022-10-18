#include <twinzo/tdevkit/tdevkit.hpp>

template <class HttpClient>
auto tDevkit<HttpClient>::getAreas(const std::vector<NetworkQuery> &query)
    -> std::vector<AreaContract> {
  auto response = this->serviceRequest<AreaContractList, void *>(
      NetworkMethod::Get, "/api/v3/areas", nullptr,
      std::vector<NetworkHeader>(), query
  );

  // Deserialize the repeating field into a vector
  return std::vector<AreaContract>(
      response.contracts().begin(), response.contracts().end()
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::getArea(
    const int &id, const std::vector<NetworkQuery> &query
) -> AreaContract {
  return this->serviceRequest<AreaContract, void *>(
      NetworkMethod::Get, "/api/v3/areas/" + std::to_string(id), nullptr,
      std::vector<NetworkHeader>(), query
  );
}