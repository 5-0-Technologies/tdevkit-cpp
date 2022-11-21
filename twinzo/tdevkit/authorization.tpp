#include <twinzo/tdevkit/tdevkit.hpp>

template <class HttpClient>
auto tDevkit<HttpClient>::setAuthHeaders(
    std::string client_guid, std::string branch_guid, std::string token
) -> void {
  this->client_guid = client_guid;
  this->branch_guid = branch_guid;
  this->token       = token;
}

template <class HttpClient>
auto tDevkit<HttpClient>::deleteCurrentToken() -> void {
  this->serviceRequest<void, void*>(
      NetworkMethod::Delete, "/api/v3/Authorization/Token", nullptr
  );
}

template <class HttpClient>
auto tDevkit<HttpClient>::getToken() -> AuthenticationResponseContract const {
  auto response = this->serviceRequest<AuthenticationResponseContract, void*>(
      NetworkMethod::Get, "/api/v3/Authorization/Token", nullptr
  );

  // Update credentials
  this->setAuthHeaders(response.client(), response.branch(), response.token());

  return response;
}

template <class HttpClient>
auto tDevkit<HttpClient>::authenticate(const CredentialContract& credentials)
    -> AuthenticationResponseContract const {
  auto response =
      this->serviceRequest<AuthenticationResponseContract, CredentialContract>(
          NetworkMethod::Post, "/api/v3/Authorization/Authenticate", credentials
      );

  // Update credentials
  this->setAuthHeaders(response.client(), response.branch(), response.token());

  return response;
}

template <class HttpClient>
auto tDevkit<HttpClient>::authenticate(
    std::string client, std::string login, std::string password
) -> AuthenticationResponseContract const {
  // Save login credentials
  this->client   = client;
  this->login    = login;
  this->password = password;

  // Construct credentials from provided arguments
  auto credentials = CredentialContract();
  credentials.set_client(client);
  credentials.set_login(login);
  credentials.set_password(password);

  return authenticate(credentials);
}

template <class HttpClient>
auto tDevkit<HttpClient>::authenticate()
    -> AuthenticationResponseContract const {
  return this->authenticate(this->client, this->login, this->password);
}