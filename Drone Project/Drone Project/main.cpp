#include "DroneClient.h"

// the IO service that handles our asynchronous actions
boost::asio::io_service io_service;

int main(int argc, char* argv[])
{
	// create the client using asynchronous IO service
	DroneClient* drone = new DroneClient(io_service);

	// create the client using asynchronous IO service using the Simulator in the VELC on 192.168.10.97
	DroneClient* drone = new DroneClient(io_service, "192.168.10.97", "192.168.10.33");  // ** entspricht der Nummer auf dem Monitor (oben rechts)

	// Enable Keyboard interaction
	drone->setHandleKeyboardInput(true);

	// start the asynchronous loop
	io_service.run();

	// if finished clear everything and safely shutdown all network connections
	DroneClient::destroyAllInstances();
	return 0;
}