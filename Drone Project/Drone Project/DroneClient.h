#ifndef DRONE_CLIENT_H
#define DRONE_CLIENT_H
#include <stdlib.h>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes/clock.hpp> 
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include "navdata.h"

const unsigned __int32 NETWORK_NAVDATA_PORT=5554;
const unsigned __int32 NETWORK_CTRL_PORT=5556;
const unsigned __int32 NETWORK_CONFIG_PORT=5559;
const unsigned __int32 NETWORK_VIDEO_PORT=5555;
const std::string NETWORK_MULTICAST_ADDRESS="224.1.1.1";
const int START_BIT = (1 << 18) | (1 << 20) | (1 << 22) | (1 << 24) | (1 << 28);
 
class DroneClient
{
public:
	DroneClient(boost::asio::io_service& io_service, std::string droneAddress = "192.168.1.1", std::string localAddress = "");
  virtual ~DroneClient();

  // Methods to override from subclasses
  // Diese Methode wird immer aufgerufen wenn die Drohne Navdata schickt. Sie gibt diese Daten auf der Konsole aus
  virtual void handleNavdataDemo(NavdataHeader* header,NavdataDemo* data);

  // Diese Methode wird immer aufgerufen wenn die Drohne Informationen zu Tags schickt, sie gibt diese dann aus der Sicht der Kamera aus
  virtual void handleARTag(NavdataHeader* header, NavdataVisionDetect* data);

  // Alle anderen Paketet werden durch diese Methode behandelt
  virtual void handleOtherPackage(NavdataHeader* header,unsigned char* rawData, unsigned long rawSize);
  virtual void updateDroneConfiguration();

  // getter/setter
  void setHandleKeyboardInput(bool enabled);
  bool isHandleKeyboardInputEnabled();

  // sending drone commands
  void sendATCommand(std::string type,std::string command);
  void sendContinousATCommand(std::string type, std::string command);
  void stopContinousATCommand();

  // helper functions
  static std::string droneFloat(float f);
  std::vector<std::string> stateToStringVector(unsigned __int32 state);
  
  // cleanup
  static void destroyAllInstances();

private:
  
  void callbackRecieveNavdata(const boost::system::error_code& error, size_t bytes_recvd);
  void callbackRecieveCtrldata(const boost::system::error_code& error, size_t bytes_recvd);
  void callbackRecieveConfigdata(const boost::system::error_code& error, size_t bytes_recvd);
  void callbackKeyInput(const boost::system::error_code &ec);
  void handleCmdTimer(const boost::system::error_code &ec);

  boost::asio::ip::address localIPAddress;
  boost::asio::ip::udp::socket navSocket;
  boost::asio::ip::udp::socket ctrlSocket;
  boost::asio::ip::tcp::socket configurationSocket;
  boost::asio::ip::udp::endpoint senderEndpoint_;
  boost::asio::ip::udp::endpoint navEndpoint;
  boost::asio::ip::udp::endpoint ctrlEndpoint;
  boost::asio::ip::tcp::endpoint configEndpoint;
  boost::asio::ip::udp::endpoint ctrlSenderEndpoint;
  boost::asio::deadline_timer keyTimer; // timer zum aufrruf des Kayboard Handlers
  boost::asio::deadline_timer cmdTimer; // timer zum senden von Paketen


  std::string continousType = "";
  std::string continousCommand = "";
  static std::vector<DroneClient*> instances;


  HANDLE hStdin;
  bool handleKeyInput;
  unsigned __int32 navdataOptions;
  unsigned __int16 sequenceCounter;
  enum { max_length = 8192 };
  char data_[max_length];
  char ctrlData[max_length];
};


#endif