#include <twinzo/tdevkit/tdevkit.hpp>

template <class HttpClient>
auto tDevkit<HttpClient>::getBranchConfiguration(const std::string& key)
    -> std::string {
  return this->serviceRequest<std::string, void*>(
      NetworkMethod::Get, "/api/v3/configuration/branch/" + key, nullptr, {},
      {}, "application/json"
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::getAccountConfiguration(const std::string& key)
    -> std::string {
  return this->serviceRequest<std::string, void*>(
      NetworkMethod::Get, "/api/v3/configuration/account/" + key, nullptr, {},
      {}, "application/json"
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::getAccountConfiguration(
    const std::string& login, const std::string& key
) -> std::string {
  return this->serviceRequest<std::string, void*>(
      NetworkMethod::Get, "/api/v3/configuration/account/" + login + "/" + key,
      nullptr, {}, {}, "application/json"
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::getConfigurationLastChange(const std::string& key)
    -> int64_t {
  auto response = this->serviceRequest<std::string, void*>(
      NetworkMethod::Get, "/api/v3/configuration/" + key + "/last-change",
      nullptr, {}, {}, "application/json"
  );

  return std::stol(response);
}