#include <stdlib.h>
#include <iostream>
#include <string>
#include "DroneClient.h"

// declare method for later use
BOOL WINAPI ConsoleHandler(DWORD CEvent);

// instantiate static variable
std::vector<DroneClient*> DroneClient::instances;

/*******************************************************************************************************************************************

Defaul Handler methods should be overriden when extending the DroneClient

********************************************************************************************************************************************/

/** The default handler for unknown data from the drone
*/
void DroneClient::handleOtherPackage(NavdataHeader* header, unsigned char* rawData, unsigned long rawSize)
{
	unsigned short* tag = (unsigned short*)(rawData);
	unsigned short* size = (unsigned short*)(rawData + 2);
	system("cls");
	std::cout << "Recieving unknown package:" << *tag << " of size " << *size << " bytes, available are " << (rawSize) << " bytes " << std::endl;
	std::vector<std::string> state = stateToStringVector(header->ardrone_state);
	std::cout << "Drone State:";
	for (std::vector<std::string>::iterator it = state.begin(); it < state.end(); it++)
		std::cout << " -- " << *it << std::endl;
	std::cout << std::endl;
}

/** The default handler for navdata from the drone, which prints it to the console always clearing it
*/
void DroneClient::handleNavdataDemo(NavdataHeader* header, NavdataDemo* navdata)
{
	return;
	system("cls");
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "DroneState:" << std::endl;
	std::vector<std::string> state = stateToStringVector(header->ardrone_state);
	for (std::vector<std::string>::iterator it = state.begin(); it < state.end(); it++) 
		std::cout << " -- " << *it << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "Velocity:" << navdata->vx << "," << navdata->vy << "," << navdata->vz << std::endl;
	std::cout << "Yaw/Roll/Pitch:" << navdata->yaw*0.001f << "deg, " << navdata->roll*0.001f << "deg, " << navdata->pitch*0.001f << "deg" << std::endl;
	std::cout << "Active camera detection:" << navdata->detection_camera_type << std::endl;
	std::cout << "Battery:" << navdata->vbat_flying_percentage << "mV" << std::endl;

}

/** The default handler for AR tags prints the tags in a square to identify there position
*/
void DroneClient::handleARTag(NavdataHeader* header, NavdataVisionDetect* data)
{
	system("cls");
	std::cout << "Detected AR Tags:" << data->nb_detected << std::endl;
	int gridX = 50;
	int gridY = 20;
	for (int y = 0; y < gridY; y++)
	{
		for (int x = 0; x < gridX; x++)
		{
			bool printedTag = false;
			for (unsigned int t = 0; t < data->nb_detected; t++)
			{
				if (data->xc[t] / (1000 / gridX) == x && data->yc[t] / (1000 / gridY) == y)
				{
					std::cout << t;
					printedTag = true;
				}
			}
			if (!printedTag)
			{
				if (y == 0 || y == gridY - 1)
					std::cout << "-";
				else if (x == 0 || x == gridX - 1)
					std::cout << "|";
				else
					std::cout << " ";
				if (x == gridX - 1)
					std::cout << std::endl;
			}
		}
	}
	for (unsigned int t = 0; t < data->nb_detected; t++)
	{
		std::cout << "Tag " << t << "(" << data->type[t] << " on camera " << data->camera_source[t] << "), dist:" << data->dist[t] << ", pos:" << data->xc[t] << "," << data->yc[t] << std::endl;
	}

}


/* sends the drone configuration, sometimes necessary for resets and such things, can also be overriden
*/
void DroneClient::updateDroneConfiguration()
{

	// To recieve navigation data, we need to send an initialization packet to the navdata port on the drone
	std::vector<unsigned char> zeroPacket;
	zeroPacket.push_back(0x01);
	zeroPacket.push_back(0x00);
	zeroPacket.push_back(0x00);
	zeroPacket.push_back(0x00);
	navSocket.send_to(boost::asio::buffer(zeroPacket), navEndpoint);
	BOOST_LOG_TRIVIAL(info) << "Send initialization packet to navigation endpoint on Drone ";

	// we want to recieve navigation data
	sendATCommand("CONFIG", "\"general:navdata_demo\",\"TRUE\"");
	sendATCommand("CTRL", "0,0");

	// we set our session parameters
	sendATCommand("CONFIG", "\"custom:session_id\", \"test\"");
	sendATCommand("CONFIG", "\"custom:profile_id\", \"EII\"");
	sendATCommand("CONFIG", "\"custom:application_id\", \"DroneClient\"");
	sendATCommand("CTRL", "0,0");
	sendATCommand("CONFIG", "\"control:euler_angle_max\", \"" + droneFloat(0.25f) + "\"");
	
	sendATCommand("PMODE", "2");
	sendATCommand("MISC", "2,20,2000,3000");
	Sleep(120);
	
	sendATCommand("REF", boost::lexical_cast<std::string>(START_BIT));


	// we set the elements we want to be in the navigation data
	navdataOptions =
		navdataOptionMask(NavDataOptions::DEMO)
		| navdataOptionMask(NavDataOptions::VISION_DETECT)
		| navdataOptionMask(NavDataOptions::ALTITUDE)
		| navdataOptionMask(NavDataOptions::VISION)
		| navdataOptionMask(NavDataOptions::VISION_OF)
		| navdataOptionMask(NavDataOptions::VISION_RAW)
		| navdataOptionMask(NavDataOptions::WIND_SPEED)
		| navdataOptionMask(NavDataOptions::VISION_DETECT);
	sendATCommand("CONFIG", "\"general:navdata_options\",\"" + boost::lexical_cast<std::string>(navdataOptions)+"\"");
	sendATCommand("CONFIG", "\"control:flight_without_shell\",\"FALSE\"");
	sendATCommand("CONFIG", "\"control:control_level\",\"1\"");
	// setup AR tracking parameters to detect color tags with the front camera and roundel tags with the bottom camera
	sendATCommand("CONFIG", "\"detect:detect_type\",\"" + boost::lexical_cast<std::string>(CAD_TYPE_MULTIPLE_DETECTION_MODE)+"\"");
	sendATCommand("CONFIG", "\"detect:enemy_colors\",\"3\"");
	sendATCommand("CONFIG", "\"detect:enemy_without_shell\",\"1\"");
	sendATCommand("CONFIG", "\"detect:detections_select_h\",\"" + boost::lexical_cast<std::string>(TAG_TYPE_SHELL_TAG_V2)+"\"");
	sendATCommand("CONFIG", "\"detect:detections_select_v\",\"" + boost::lexical_cast<std::string>(TAG_TYPE_NONE)+"\"");
	sendATCommand("CONFIG", "\"detect:detections_select_v_hsync\",\"" + boost::lexical_cast<std::string>(TAG_TYPE_BLACK_ROUNDEL)+"\"");

	// send the control commands to acknowledge the configuration an retrieve the drone internal configuration
	sendATCommand("CTRL", "0,0");
	sendATCommand("CTRL", "5,0");
	sendATCommand("CTRL", "4,0");
	
}


/********************************************************************************************************************************************

********************************************************************************************************************************************/

/* Constructr creates all the sockets for the network communication

*/
DroneClient::DroneClient(boost::asio::io_service& io_service, std::string droneAddress, std::string localAddress)
: navSocket(io_service)
, ctrlSocket(io_service)
, sequenceCounter(1)
, handleKeyInput(false)
, configurationSocket(io_service)
, keyTimer(io_service, boost::posix_time::milliseconds(100))
, cmdTimer(io_service, boost::posix_time::milliseconds(150))
{
	BOOST_LOG_TRIVIAL(info) << "setting up Drone Client";

	// we create the endpoints for the communication to the drone, for navigation, control and configuration
	navEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(droneAddress), NETWORK_NAVDATA_PORT);
	ctrlEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(droneAddress), NETWORK_CTRL_PORT);
	configEndpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(droneAddress), NETWORK_CONFIG_PORT);


	// The ARDrone assigns IPAddresses between 192.168.2 and 192.168.5
	// So we need to test all those adresses. An exception happens if the localAddress is specified in the constructor
	// To find the correct address we try to bind the socket to all of these adresses and wait until we succeed
	// we then use this socket for navigation data
	long droneConnectionID = 2;
	std::string localIPAddressPrefix = "192.168.1.";
	boost::system::error_code ec;
	while (droneConnectionID < 6)
	{
		ec.clear(); // clear error value
		// check if a manual address is givin, for the simulator for example
		if (localAddress.empty())
			localIPAddress = boost::asio::ip::address::from_string(localIPAddressPrefix + boost::lexical_cast<std::string>(droneConnectionID));
		else
			localIPAddress = boost::asio::ip::address::from_string(localAddress);// boost::asio::ip::address::from_string(localIPAddressPrefix + boost::lexical_cast<std::string>(droneConnectionID));
		droneConnectionID++;
		boost::asio::ip::udp::endpoint listen_endpoint(localIPAddress, NETWORK_NAVDATA_PORT);
		navSocket.open(listen_endpoint.protocol(), ec);
		// Create the socket so that multiple may be bound to the same address.
		navSocket.set_option(boost::asio::ip::udp::socket::reuse_address(true), ec);
		navSocket.set_option(boost::asio::ip::multicast::enable_loopback(true), ec);
		navSocket.bind(listen_endpoint, ec);
		if (ec) // socket creation failed, continue with next ip
			continue;

		// Join the multicast group, to recieve multicast navigation data
		navSocket.set_option(
			boost::asio::ip::multicast::join_group(boost::asio::ip::address::from_string(NETWORK_MULTICAST_ADDRESS).to_v4()), ec);
		if (ec)
			throw std::exception("Could not join multicast group:");
		break;
	}
	if (ec)
		throw std::exception(("Could not bind to any socket:" + localIPAddressPrefix + "[2|3|4|5]:" + boost::lexical_cast<std::string>(NETWORK_NAVDATA_PORT)).c_str());

	// We now have our navigation data socket up
	BOOST_LOG_TRIVIAL(info) << "Setup listening UDP socket on " << localIPAddress.to_string() << ":" << NETWORK_NAVDATA_PORT;
	ec.clear();

	// setup control socket to send control commands
	ctrlSocket.open(boost::asio::ip::udp::v4());
	ctrlSocket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
	ctrlSocket.bind(boost::asio::ip::udp::endpoint(localIPAddress, NETWORK_CTRL_PORT));
	BOOST_LOG_TRIVIAL(info) << "Setup listening UDP socket on " << localIPAddress.to_string() << ":" << NETWORK_CTRL_PORT;

	// setup config socket to recieve configurations
	configurationSocket.open(boost::asio::ip::tcp::v4());
	configurationSocket.set_option(boost::asio::ip::tcp::socket::reuse_address(true));
	configurationSocket.connect(configEndpoint,ec);
	if (!ec) {
		BOOST_LOG_TRIVIAL(info) << "Setup connection to Config TCP socket on " << localIPAddress.to_string() << ":" << NETWORK_CONFIG_PORT;
		configurationSocket.async_read_some(
			boost::asio::buffer(ctrlData, max_length),
			boost::bind(&DroneClient::callbackRecieveConfigdata, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}
	// Start asynchronously recieving data on all created sockets
	navSocket.async_receive_from(
		boost::asio::buffer(data_, max_length), senderEndpoint_,
		boost::bind(&DroneClient::callbackRecieveNavdata, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));

	ctrlSocket.async_receive_from(
		boost::asio::buffer(ctrlData, max_length), ctrlSenderEndpoint,
		boost::bind(&DroneClient::callbackRecieveCtrldata, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
		

	// Send initial configuration and setup commands to the drone
	updateDroneConfiguration();

	// Setup console input reading
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(hStdin, ENABLE_WINDOW_INPUT);

	// setup handler to catch closing of console usng Win32 API
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE) == FALSE)
		throw std::exception("Unable to install console handler!");

	handleCmdTimer(boost::system::error_code());

	// the instances vector keeps track of all created drones, important to cleanly close all network communications
	instances.push_back(this);
}


/** The Destructor shuts down all sockets and closes them, we ignore the error codes that are generated in this case
*/
DroneClient::~DroneClient()
{
	if (ctrlSocket.is_open())
	{
		// land the drone
		this->sendATCommand("REF", boost::lexical_cast<std::string>(0));
	}
	cmdTimer.cancel();
	keyTimer.cancel();
	// stop the io_service
	navSocket.get_io_service().stop();
	// sleep a bit to give the io-service time to stop
	boost::this_thread::sleep(boost::posix_time::milliseconds(500));

	// shutdown all network sockets
	boost::system::error_code ec;
	navSocket.shutdown(boost::asio::socket_base::shutdown_both, ec);
	ctrlSocket.shutdown(boost::asio::socket_base::shutdown_both, ec);
	configurationSocket.shutdown(boost::asio::socket_base::shutdown_both, ec);
	navSocket.close(ec);
	ctrlSocket.close(ec);
	configurationSocket.close(ec);
	BOOST_LOG_TRIVIAL(info) << "DroneClient destroyed, all sockets closed";
}

/**
* the method creates the appropriate AT command out of an type and parameters,
* it handles the sequence number, basic format and adds session information for CONFIG commands
*/
void DroneClient::sendATCommand(std::string type, std::string command)
{
	std::string message = "AT*" + type + "=" + boost::lexical_cast<std::string>(sequenceCounter++) + (command.empty() ? "" : "," + command) + "\r";
	// If we have a configuration message, we need to send the correct IDs
	if (type == "CONFIG")
		message = "AT*CONFIG_IDS=" + boost::lexical_cast<std::string>(sequenceCounter++) + "\"test\",\"EII\",\"DroneClient\"\r" + message;

	ctrlSocket.send_to(boost::asio::buffer(message), ctrlEndpoint);
}
/* calling a command will resend it everytime navdata arrives at the drone.
* it will not stop if a single command is send!
*/
void DroneClient::sendContinousATCommand(std::string type, std::string command)
{
	this->continousType = type;
	this->continousCommand = command;
}

/* stop sending continous commands */
void DroneClient::stopContinousATCommand()
{
	this->continousType = "";
	this->continousCommand = "";
}


/** handles control messages from the drone
*/
void DroneClient::callbackRecieveCtrldata(const boost::system::error_code& error,
	size_t bytes_recvd)
{
	if (error) {
		BOOST_LOG_TRIVIAL(error) << "Error recieving ctrl-data: " << error;
		boost::this_thread::sleep(boost::posix_time::milliseconds(500));
	}
	else
		BOOST_LOG_TRIVIAL(info) << "CTRL: recieved " << bytes_recvd << " Bytes";
	try {
		ctrlSocket.async_receive_from(
			boost::asio::buffer(ctrlData, max_length), ctrlSenderEndpoint,
			boost::bind(&DroneClient::callbackRecieveCtrldata, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}
	catch (std::exception e) {
		BOOST_LOG_TRIVIAL(error) << "Error recieving ctrl data";
	}
}

/** handles config messages from the drone
*/
void DroneClient::callbackRecieveConfigdata(const boost::system::error_code& error,
	size_t bytes_recvd)
{
	if (error)
		BOOST_LOG_TRIVIAL(error) << "Error recieving config-data: " << error;
	else
		BOOST_LOG_TRIVIAL(info) << "CONFIG: recieved " << bytes_recvd << " Bytes";
	try {
		ctrlData[bytes_recvd] = 0;
		BOOST_LOG_TRIVIAL(debug) << ctrlData;
		configurationSocket.async_read_some(
			boost::asio::buffer(ctrlData, max_length),
			boost::bind(&DroneClient::callbackRecieveConfigdata, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}
	catch (std::exception e) {
		BOOST_LOG_TRIVIAL(error) << "Error recieving CONFIG data";
	}
}


/** handles reception of messages over the multicast socket, it calls handler functions depending on the type of package
*/
void DroneClient::callbackRecieveNavdata(const boost::system::error_code& error_code,
	size_t bytes_recvd)
{

	unsigned char* rawData = (unsigned char*)&(data_[0]);
	if (error_code)
	{
		BOOST_LOG_TRIVIAL(error) << "Error recieving data" << error_code;
	}
	else
	{
		NavdataHeader* header = (NavdataHeader*)rawData;
		rawData += sizeof(NavdataHeader);
		while (rawData < ((unsigned char*)&(data_[0]) + bytes_recvd))
		{
			// identify the tag to call the correct handler function
			unsigned short* tag = (unsigned short*)(rawData);
			unsigned short* size = (unsigned short*)(rawData + 2);
			switch (*tag)
			{
			case 0:
				handleNavdataDemo(header, (NavdataDemo*)(rawData));
				break;
			case 16:
				handleARTag(header, (NavdataVisionDetect*)(rawData));
				break;
			case 9://pwm
				break;
			case 20://games
				break;
			case 22: //magneto
				break;
			case 25: //hdVideoStream
				break;
			case 26: //wifi
				break;
			case 27: //zimmu3000
				break;
			case 65535://checksum
				break;
				/*
					1 : 'time',
					2 : 'rawMeasures',
					3 : 'phyMeasures',
					4 : 'gyrosOffsets',
					5 : 'eulerAngles',
					6 : 'references',
					7 : 'trims',
					8 : 'rcReferences',
					9 : 'pwm',
					10 : 'altitude',
					11 : 'visionRaw',
					12 : 'visionOf',
					13 : 'vision',
					14 : 'visionPerf',
					15 : 'trackersSend',
					16 : 'visionDetect',
					17 : 'watchdog',
					18 : 'adcDataFrame',
					19 : 'videoStream',
					20 : 'games',
					21 : 'pressureRaw',
					22 : 'magneto',
					23 : 'windSpeed',
					24 : 'kalmanPressure',
					25 : 'hdvideoStream',
					26 : 'wifi',
					27 : 'zimmu3000',
					*/
			default:
				//BOOST_LOG_TRIVIAL(info) << "Recieving unknown package:" << *tag << " of size " << *size << " bytes, available are " << (bytes_recvd - sizeof(NavdataHeader)) << " bytes ";
				break;
			}
			rawData += *size;
		}
		// reset watchdog, if we do not send enough packets
		if (header->ardrone_state & ARDRONE_COM_WATCHDOG_MASK)
		{
			sendATCommand("COMWDG", "");
		}

	}
	// continue recieving packets
	navSocket.async_receive_from(
		boost::asio::buffer(data_, max_length), senderEndpoint_,
		boost::bind(&DroneClient::callbackRecieveNavdata, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}


void DroneClient::setHandleKeyboardInput(bool enabled)
{
	if (handleKeyInput == enabled)
		return;
	// if keyboard handler should be started, set the timer to execute handle_key_input
	if (enabled)
		keyTimer.async_wait(
		boost::bind(&DroneClient::callbackKeyInput, this,
		boost::asio::placeholders::error));
	else // if disabled, cancel pending waits
		keyTimer.cancel();
	handleKeyInput = enabled;
}
bool DroneClient::isHandleKeyboardInputEnabled()
{
	return handleKeyInput;
}

void  DroneClient::handleCmdTimer(const boost::system::error_code &ec)
{
	if (ec == boost::asio::error::operation_aborted)
		return;
	static int watchdog = 0;

	// send watchdog every 200ms to permit the watchdog timer on the drone
	if (watchdog==0)
		sendATCommand("COMWDG", "");
	watchdog = (watchdog + 1) % 8;
	if (!continousType.empty())
		sendATCommand(continousType, continousCommand);

	// Restart Cmd handler
	cmdTimer.async_wait(
		boost::bind(&DroneClient::handleCmdTimer, this,
		boost::asio::placeholders::error));

}

/* handles keyboard events, it queries the windows API for the KeyBuffer and reads the newest key from the buffer and executes the appropriate control command
*/
void DroneClient::callbackKeyInput(const boost::system::error_code &ec)
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
			case '4': //links
				sendContinousATCommand("PCMD", "1," + DroneClient::droneFloat(-0.2f) + ",0,0,0");
				break;
			case '6': //rechts
				sendContinousATCommand("PCMD", "1," + DroneClient::droneFloat(0.2f) + ",0,0,0");
				break;
			case '8': //vorne
				sendContinousATCommand("PCMD", "1,0," + DroneClient::droneFloat(-0.2f) + ",0,0");
				break;
			case '2': //hinten
				sendContinousATCommand("PCMD", "1,0," + DroneClient::droneFloat(0.2f) + ",0,0");
				break;
			case '7': //rotation links
				sendContinousATCommand("PCMD", "1,0,0,0," + DroneClient::droneFloat(-0.5f));
				break;
			case '9': //rotation rechts
				sendContinousATCommand("PCMD", "1,0,0,0," + DroneClient::droneFloat(0.5f));
				break;
			case '+': //aufstieg
				sendContinousATCommand("PCMD", "1,0,0," + DroneClient::droneFloat(0.5f) + ",0");
				break;
			case '-': //abstieg
				sendContinousATCommand("PCMD", "1,0,0," + DroneClient::droneFloat(-0.5f) + ",0");
				break;
			case '0': // landen
				sendATCommand("REF", boost::lexical_cast<std::string>(START_BIT));
				break;
			case 's': // starten
				sendATCommand("FTRIM", "");
				sendATCommand("REF", boost::lexical_cast<std::string>(START_BIT | (1 << 9)));
				sendContinousATCommand("PCMD", "0,0,0,0,0");
				break;
			case 'e': // emergency
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
		boost::bind(&DroneClient::callbackKeyInput, this,
		boost::asio::placeholders::error));
}


std::string DroneClient::droneFloat(float f)
{
	__int32 value = *(__int32*)&f;
	return boost::lexical_cast<std::string>(value);
}


/** A helper function to convert state IDs to meaningfull strings
*/
std::vector<std::string> DroneClient::stateToStringVector(unsigned __int32 state)
{
	std::vector<std::string> stateVector;
	if (state & ARDRONE_FLY_MASK) stateVector.push_back("fly");
	if (state & ARDRONE_VIDEO_MASK) stateVector.push_back("video");
	if (state & ARDRONE_VISION_MASK) stateVector.push_back("vision");
	if (state & ARDRONE_CONTROL_MASK) stateVector.push_back("control");
	if (state & ARDRONE_ALTITUDE_MASK) stateVector.push_back("altitude");
	if (state & ARDRONE_USER_FEEDBACK_START) stateVector.push_back("user_feedback");
	if (state & ARDRONE_COMMAND_MASK) stateVector.push_back("command");
	if (state & ARDRONE_FW_FILE_MASK) stateVector.push_back("FW_files");
	if (state & ARDRONE_FW_VER_MASK) stateVector.push_back("FW_version");
	if (state & ARDRONE_NAVDATA_DEMO_MASK) stateVector.push_back("navdata_demo");
	if (state & ARDRONE_NAVDATA_BOOTSTRAP) stateVector.push_back("navdata_bootstrap");
	if (state & ARDRONE_MOTORS_MASK) stateVector.push_back("motors");
	if (state & ARDRONE_COM_LOST_MASK) stateVector.push_back("com_lost");
	if (state & ARDRONE_VBAT_LOW) stateVector.push_back("VBAT-low");
	if (state & ARDRONE_USER_EL) stateVector.push_back("user-EL");
	if (state & ARDRONE_TIMER_ELAPSED) stateVector.push_back("timer-elapsed");
	if (state & ARDRONE_ANGLES_OUT_OF_RANGE) stateVector.push_back("angles-out-of-range");
	if (state & ARDRONE_ULTRASOUND_MASK) stateVector.push_back("ultrasound");
	if (state & ARDRONE_CUTOUT_MASK) stateVector.push_back("cutout");
	if (state & ARDRONE_PIC_VERSION_MASK) stateVector.push_back("PIC-version");
	if (state & ARDRONE_ATCODEC_THREAD_ON) stateVector.push_back("ATCodec-thread-on");
	if (state & ARDRONE_NAVDATA_THREAD_ON) stateVector.push_back("Navdata-thread-on");
	if (state & ARDRONE_VIDEO_THREAD_ON) stateVector.push_back("Video-thread-on");
	if (state & ARDRONE_ACQ_THREAD_ON) stateVector.push_back("ACQ-thread-on");
	if (state & ARDRONE_CTRL_WATCHDOG_MASK) stateVector.push_back("CTRL-watchdog");
	if (state & ARDRONE_ADC_WATCHDOG_MASK) stateVector.push_back("ADC-watchdog");
	if (state & ARDRONE_COM_WATCHDOG_MASK) stateVector.push_back("COM-watchdog");
	if (state & ARDRONE_EMERGENCY_MASK)stateVector.push_back("Emergency");
	return stateVector;
}
void DroneClient::destroyAllInstances()
{
	for (unsigned int i = 0; i < instances.size(); i++)
		delete instances[i];
	instances.empty();
}

/** Handler to react on console close
*/
BOOL WINAPI ConsoleHandler(DWORD CEvent)
{
	BOOST_LOG_TRIVIAL(info) << "stopping io-service";
	DroneClient::destroyAllInstances();
	BOOST_LOG_TRIVIAL(info) << "stopped io-service";
	return TRUE;
}

