#include <stdexcept>

class ServerResponseException : public std::runtime_error {
protected:
  int status_code;

public:
  ServerResponseException(int status_code_, const std::string& what_arg)
      : status_code(status_code_), std::runtime_error(what_arg) {}
  ServerResponseException(int status_code_, const char* what_arg)
      : status_code(status_code_), std::runtime_error(what_arg) {}

  int get_status_code() const {
    return status_code;
  }
};

class NetworkException : public std::runtime_error {
protected:
  int client_specific_error_code;

public:
  NetworkException(int code, const std::string& what_arg)
      : client_specific_error_code(code), std::runtime_error(what_arg) {}
  NetworkException(int code, const char* what_arg)
      : client_specific_error_code(code), std::runtime_error(what_arg) {}

  int get_client_specific_error_code() const {
    return client_specific_error_code;
  }
};