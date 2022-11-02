#pragma once

#include <memory>
#include <twinzo/network/exceptions.hpp>
#include <twinzo/tdevkit/tdevkit.hpp>

template <class HttpClient>
tDevkit<HttpClient>::tDevkit(std::string hostname, int port) {
  m_network_client = std::make_unique<HttpClient>(hostname, port);
  m_network_client->connect();
}

template <class HttpClient>
tDevkit<HttpClient>::~tDevkit() {
  m_network_client->disconnect();
}

template <class HttpClient>
template <class ResponseContract, class PayloadContract>
auto tDevkit<HttpClient>::serviceRequest(
    NetworkMethod method, std::string path, PayloadContract data,
    const std::vector<NetworkHeader>& headers,
    const std::vector<NetworkQuery>& query, const std::string& content_type
) -> ResponseContract {
  std::vector<NetworkHeader> static_headers = {
      std::make_pair("Client", m_client_guid),
      std::make_pair("Branch", m_branch_guid), std::make_pair("Token", m_token),
      std::make_pair("Content-Type", content_type),
      std::make_pair("Accept", content_type)};

  // Prepare request
  NetworkRequest request;
  request.url = path;
  // Attach static headers
  request.headers.insert(
      request.headers.begin(), static_headers.begin(), static_headers.end()
  );
  // Attach user-provided headers
  request.headers.insert(
      request.headers.begin(), headers.begin(), headers.end()
  );

  std::unique_ptr<NetworkPayload> payload;

  // Serialize protobuf contract if payload Contract type is given
  if constexpr (!std::is_same_v<PayloadContract, void*>) {
    payload = std::make_unique<NetworkPayload>();
    // TODO: error handling
    data.SerializeToString(payload.get());
  }

  NetworkResponse response =
      m_network_client->request(method, request, payload.get());

  if (response.status_code / 100 != 2) {
    throw ServerResponseException(response.status_code, response.status_line);
  }

  // Return unserialized string if requested
  if constexpr (std::is_same_v<ResponseContract, std::string>) {
    return response.payload;
  }
  // Parse payload from the response if type other than void* is given
  else if constexpr (!std::is_same_v<ResponseContract, void>) {
    ResponseContract contract;

    // Do not parse payload into a contract if it is empty
    // Note: this can happen with any contract whose contents are either
    // all optional, or repeated
    if (response.payload.size() > 0) {
      // TODO: error handling
      contract.ParseFromString(response.payload);
    }

    return contract;
  }
}
