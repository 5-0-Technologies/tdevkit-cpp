#include <twinzo/network/mock_client.hpp>
#include <twinzo/tdevkit/tdevkit.hpp>

// #include <twinzo/data/device_contract.pb.h>

int main(int argc, char const *argv[]) {
  tDevkit<MockNetworkClient> devkit("hostname", 80);
  return 0;
}
