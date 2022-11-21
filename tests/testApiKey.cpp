// #include <tDevkit/mock-network-client/MockNetworkClient.hpp>
#include <QApplication>
#include <twinzo/network/qt_client.hpp>
#include <twinzo/tdevkit/tdevkit.hpp>

int main(int argc, char *argv[]) {
  // Initialize QT application
  qputenv("QT_QPA_PLATFORM", "offscreen");
  QApplication app(argc, argv);

  tDevkit<QtNetworkClient> devkit("https://develop.portal.twinzo.eu", 443);

  devkit.client_guid = "00000000-0000-0000-0000-000000000001";
  devkit.branch_guid = "00000000-0000-0000-0000-000000000003";
  devkit.api_key     = "X1fprPtlkvolW1Bl47UQV4SoW8siY3n8QDQkDsGJ";

  auto devices = devkit.getDevices();

  return 0;
}