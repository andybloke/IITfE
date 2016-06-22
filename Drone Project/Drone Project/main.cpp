#include "DroneClient.h"

// the IO service that handles our asynchronous actions
boost::asio::io_service io_service;

class MyDroneClient : public DroneClient
{
public:
	MyDroneClient(boost::asio::io_service& service) :DroneClient(service)
	{

	}
	void callbackKeyInput(const boost::system::error_code &ec)
	{
		if (ec == boost::asio::error::operation_aborted)
			return;
		INPUT_RECORD inputEvent;
		long cNumRead;
		// First query the number of keyboard events
		GetNumberOfConsoleInputEvents(hStdin, (LPDWORD)&cNumRead);
		if (cNumRead > 0)
		{

			// if we have keyboard events read one of them
			ReadConsoleInput(hStdin, &inputEvent, 1, (LPDWORD)&cNumRead);

			if (inputEvent.EventType == KEY_EVENT && inputEvent.Event.KeyEvent.bKeyDown)
			{
				switch (inputEvent.Event.KeyEvent.uChar.AsciiChar)
				{
				case 'a': //links
					sendContinousATCommand("PCMD", "1," + DroneClient::droneFloat(-0.2f) + ",0,0,0");
					break;
				case 'd': //rechts
					sendContinousATCommand("PCMD", "1," + DroneClient::droneFloat(0.2f) + ",0,0,0");
					break;
				case 'w': //vorne
					sendContinousATCommand("PCMD", "1,0," + DroneClient::droneFloat(-0.2f) + ",0,0");
					break;
				case 's': //hinten
					sendContinousATCommand("PCMD", "1,0," + DroneClient::droneFloat(0.2f) + ",0,0");
					break;
				case 'q': //rotation links
					sendContinousATCommand("PCMD", "1,0,0,0," + DroneClient::droneFloat(-0.5f));
					break;
				case 'e': //rotation rechts
					sendContinousATCommand("PCMD", "1,0,0,0," + DroneClient::droneFloat(0.5f));
					break;
				case 'o': //aufstieg
					sendContinousATCommand("PCMD", "1,0,0," + DroneClient::droneFloat(0.5f) + ",0");
					break;
				case 'k': //abstieg
					sendContinousATCommand("PCMD", "1,0,0," + DroneClient::droneFloat(-0.5f) + ",0");
					break;
				case 'l': // landen
					sendATCommand("REF", boost::lexical_cast<std::string>(START_BIT));
					break;
				case 'p': // starten
					sendATCommand("FTRIM", "");
					sendATCommand("REF", boost::lexical_cast<std::string>(START_BIT | (1 << 9)));
					sendContinousATCommand("PCMD", "0,0,0,0,0");
					break;
				case ' ': // emergency
					sendATCommand("REF", boost::lexical_cast<std::string>(1 << 8));
					break;

				case 'r': // reset drone configuration
				{	// first send packet to navdata port
							  std::vector<unsigned char> zeroPacket;
							  zeroPacket.push_back(0x01);
							  zeroPacket.push_back(0x00);
							  zeroPacket.push_back(0x00);
							  zeroPacket.push_back(0x00);
							  navSocket.send_to(boost::asio::buffer(zeroPacket), navEndpoint);
							  updateDroneConfiguration();
							  break;
				}
				default: // stabilisieren
					sendContinousATCommand("PCMD", "0,0,0,0,0");
				}
			}
			else // when there is keyup, we stabilize 
				sendContinousATCommand("PCMD", "0,0,0,0,0");
			//		FlushConsoleInputBuffer(hStdin);
		}
		// Restart Key handler
		keyTimer.async_wait(
			boost::bind(&MyDroneClient::callbackKeyInput, this,
			boost::asio::placeholders::error));
	}

	void setHandleKeyboardInput(bool enabled)
	{
		if (handleKeyInput == enabled)
			return;
		// if keyboard handler should be started, set the timer to execute handle_key_input
		if (enabled)
			keyTimer.async_wait(
			boost::bind(&MyDroneClient::callbackKeyInput, this,
			boost::asio::placeholders::error));
		else // if disabled, cancel pending waits
			keyTimer.cancel();
		handleKeyInput = enabled;
	}

};

int main(int argc, char* argv[])
{
	// create the client using asynchronous IO service
	DroneClient* drone = new MyDroneClient(io_service);

	// create the client using asynchronous IO service using the Simulator in the VELC on 192.168.10.97
	//DroneClient* drone = new MyDroneClient(io_service, "192.168.10.97", "192.168.10.33");  // ** entspricht der Nummer auf dem Monitor (oben rechts)

	// Enable Keyboard interaction
	drone->setHandleKeyboardInput(true);

	// start the asynchronous loop
	io_service.run();

	// if finished clear everything and safely shutdown all network connections
	DroneClient::destroyAllInstances();
	return 0;
}