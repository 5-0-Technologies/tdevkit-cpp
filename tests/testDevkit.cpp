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

  tDevkit<QtNetworkClient> devkit("https://develop.portal.twinzo.eu", 443);

  AuthenticationResponseContract auth_response;

  auto credentials = CredentialContract();
  credentials.set_client("Infotech");
  credentials.set_login("tDevkit-cpp-sensor");
  credentials.set_password("tDevkit-cpp-sensor");

  auth_response = devkit.authenticate(credentials);
  // DEBUG
  std::cout << auth_response.DebugString() << std::endl;
  // TODO: validate

  auth_response = devkit.getToken();
  // DEBUG
  std::cout << auth_response.DebugString() << std::endl;
  // TODO: validate

  // Get our device's info
  auto device_info = devkit.getDevice("tDevkit-cpp-device");
  // DEBUG
  std::cout << device_info.DebugString() << std::endl;

  auto devices = devkit.getDevices();
  // DEBUG
  for (auto device : devices) {
    std::cout << device.DebugString() << std::endl;
  }
  // TODO: validate

  int rand = std::rand();

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

  // Add device
  DeviceContract device;
  device.set_login("tDevkit-cpp-test");
  device.set_branchid(device_info.branchid());
  device.set_sectorid(device_info.sectorid());
  device.set_title("tDevkit-cpp-test");
  device.set_ismoving(false);
  device.set_fallstatus(FallType::OK);
  device.set_devicetypeid(4);
  device.set_position(false);
  device.set_geofence(false);

  auto new_device = devkit.addDevice(device);
  std::cout << "Sensor created successfully:\n"
            << new_device.DebugString() << std::endl;

  // Delete device
  devkit.deleteDevice(new_device.id());
  std::cout << "Device deleted successfully" << std::endl;

  // Fetch Sensors
  auto sensors = devkit.getSensors();
  std::cout << "Received " << sensors.size() << " sensors" << std::endl;

  // Choose random device out of the list
  rand_id = 0;
  // Reroll if sensor has a colon in the login (long-standing API issue)
  while (sensors.at(rand_id).login().find(':') != std::string::npos)
    rand_id = std::rand() % (sensors.size());
  // Fetch device using the ID
  auto sensor_by_id = devkit.getSensor(sensors.at(rand_id).id());
  std::cout << sensor_by_id.DebugString() << std::endl;
  // Fetch device using the login
  auto sensor_by_login = devkit.getSensor(sensors.at(rand_id).login());
  std::cout << sensor_by_login.DebugString() << std::endl;

  SensorContract sensor;
  sensor.set_login("tDevkit-test");
  sensor.set_title("tDevkit-test");
  sensor.set_mac("00:00:00:00:00:00");

  sensor = devkit.addSensor(sensor);
  std::cout << "Sensor created successfully:\n"
            << sensor.DebugString() << std::endl;

  SensorDataBatchContract data;
  data.set_quantity("Q");
  data.set_value("V");
  data.set_unit("U");
  data.set_datatype("String");

  devkit.addSensorData({data});
  std::cout << "Sensor data added successfully" << std::endl;

  SensorBatchContract contract;
  contract.set_login("tDevkit-test");
  // Hacky solution, not advised in production
  *contract.mutable_sensordata()->Add() = data;
  devkit.addSensorData({contract});
  std::cout << "Batch sensor data added successfully" << std::endl;

  devkit.deleteSensor(sensor.id());
  std::cout << "Sensor deleted successfully" << std::endl;

  devkit.deleteCurrentToken();
  // TODO: validate

  return 0;
}
