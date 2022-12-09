//#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <string>
#include <sstream>
//#include <windows.h>
//#include <winusb.h>
//#include <WinSock2.h>
#include "adb/connection.h"
#include "adb/transport.h"
#include "adb/protocol/protocol.h"
#include "adb/protocol/serialization.h"
#include "adb/protocol/util.h"

//#pragma comment(lib, "ws2_32.lib")

//#define ABORT(MESSAGE)                                                   \
//              std::cout << MESSAGE << ": " << WSAGetLastError() << '\n'; \
//              closesocket(adb_socket);                                   \
//              WSACleanup();                                              \
//              return -1;                                                 \


int main()
{
	const adb::protocol::adb_packet packet = adb::protocol::make_packet(
		adb::protocol::adb_command::CNXN,
		adb::protocol::MAX_PAYLOAD_LEGACY,
		adb::protocol::PROTOCOL_VERSION,
		"host::test");

	std::string serialized = adb::protocol::serializer::serialize(packet);
	adb::protocol::adb_packet deserialized = adb::protocol::serializer::deserialize(serialized);

	std::cout << "Initial: " << packet << '\n';
	std::cout << "Serialized: " << serialized << '\n';
	std::cout << "Deserialized: " << deserialized << '\n';

	/*WSAData wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != NO_ERROR)
	{
		std::cout << "failed to initialize wsa" << '\n';
		return -1;
	}

	std::string::npos;

	SOCKET adb_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in address {.sin_family = AF_INET, .sin_port = htons(42261)};
	address.sin_addr.s_addr = inet_addr("192.168.100.3");
	if (connect(adb_socket, (SOCKADDR*) &address, sizeof(address)) == SOCKET_ERROR)
	{
		ABORT("Could not connect")
	}

	std::cout << "Outgoing: " << packet.as_string() << '\n';
	if (send(adb_socket, packet.as_string().c_str(), packet.size(), 0) == SOCKET_ERROR)
	{
		ABORT("Send failed")
	};

	char incoming_buf[512];
	int receive_status;
	do {
		receive_status = recv(adb_socket, incoming_buf, 512, 0);

		if (receive_status > 0)
		{
			std::cout << "Incoming: " << incoming_buf << '\n';
		} else if (receive_status == 0)
		{
			std::cout << "Connection closed" << '\n';
		}
		else 
		{
			ABORT("Failed to receive")
		}
	} while (receive_status > 0);


	if (shutdown(adb_socket, SD_SEND) == SOCKET_ERROR)
	{
		ABORT("Failed to shutdown socket")
	}

	closesocket(adb_socket);
	WSACleanup();*/

	return 0;
}