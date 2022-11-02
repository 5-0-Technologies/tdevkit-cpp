// #include <tDevkit/mock-network-client/MockNetworkClient.hpp>
#include <QApplication>
#include <twinzo/network/qt_client.hpp>
#include <twinzo/tdevkit/tdevkit.hpp>

int main(int argc, char *argv[]) {
  // Initialize QT application
  qputenv("QT_QPA_PLATFORM", "offscreen");
  QApplication app(argc, argv);

  // use current time as seed for random generator
  std::srand(std::time(nullptr));

  tDevkit<QtNetworkClient> devkit("https://portal.twinzo.eu", 443);

  AuthenticationResponseContract auth_response;

  auto credentials = CredentialContract();
  credentials.set_client("twinzo");
  credentials.set_login("tDevkit-cpp");
  credentials.set_password("tDevkit-cpp");

  auth_response = devkit.authenticate(credentials);
  // DEBUG
  std::cout << auth_response.DebugString() << std::endl;
  // TODO: validate

  auth_response = devkit.getToken();
  // DEBUG
  std::cout << auth_response.DebugString() << std::endl;
  // TODO: validate

  auto devices = devkit.getDevices();
  // DEBUG
  for (auto device : devices) {
    std::cout << device.DebugString() << std::endl;
  }
  // TODO: validate

  int rand = std::rand();
  int size = devices.size();

  // Choose random device out of the list
  int rand_id = std::rand() % (devices.size());
  // Fetch device using the ID
  auto device_by_id = devkit.getDevice(devices.at(rand_id).id());
  std::cout << device_by_id.DebugString() << std::endl;
  // Fetch device using the login
  auto device_by_login = devkit.getDevice(devices.at(rand_id).login());
  std::cout << device_by_login.DebugString() << std::endl;

  // Fetch Areas
  auto areas = devkit.getAreas();
  std::cout << "Received " << areas.size() << " areas" << std::endl;
  // TODO: validate

  devkit.deleteCurrentToken();
  // TODO: validate

  return 0;
}
