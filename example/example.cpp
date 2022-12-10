#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <WinSock2.h>
#include "adb/connection.h"
#include "adb/transport.h"
#include "adb/protocol/protocol.h"
#include "adb/protocol/serialization.h"
#include "adb/protocol/util.h"

#pragma comment(lib, "ws2_32.lib")

#define ABORT(MESSAGE)                                                   \
              std::cout << MESSAGE << ": " << WSAGetLastError() << '\n'; \
              closesocket(adb_socket);                                   \
              WSACleanup();                                              \
              return -1;                                                 \

using adb_packet = adb::protocol::adb_packet;
using adb_message = adb::protocol::adb_message;
constexpr auto make_connect_packet = adb::protocol::make_connect_packet;
constexpr auto systype_host = adb::protocol::adb_system_identity_systype::host;
constexpr auto serialize = adb::protocol::serializer::serialize;
constexpr auto deserialize = adb::protocol::serializer::deserialize;

int main()
{
	const adb_packet packet = make_connect_packet(systype_host, "fake-adb", "real-adb");
	const size_t packet_size = sizeof(adb_message) + packet.payload.size();

	WSAData wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != NO_ERROR)
	{
		std::cout << "Failed to initialize WSA: " << WSAGetLastError() << '\n';
		return -1;
	}

	SOCKET adb_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in address {.sin_family = AF_INET, .sin_port = htons(37503)}; //replace with the device's ADB port
	address.sin_addr.s_addr = inet_addr("192.168.100.3"); //replace with the device's ADB IP
	if (connect(adb_socket, (SOCKADDR*) &address, sizeof(address)) == SOCKET_ERROR)
	{
		ABORT("Could not connect")
	}

	if (send(adb_socket, serialize(packet).c_str(), packet_size, 0) == SOCKET_ERROR)
	{
		ABORT("Send failed")
	};

	char incoming_buf[512];
	int receive_status;
	do {
		receive_status = recv(adb_socket, incoming_buf, 512, 0);

		if (receive_status > 0)
		{
			adb_packet deserialized = deserialize(incoming_buf);
			std::cout << "Incoming: " << deserialized << '\n';
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
	WSACleanup();

	return 0;
}