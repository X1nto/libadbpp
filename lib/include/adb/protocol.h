#pragma once

#include <string>

namespace adb 
{ 
namespace protocol
{

constexpr int parse_message(const char in[4])
{
	return (in[3]) << 24 |
		(in[2]) << 16 |
		(in[1]) << 8 |
		(in[0]);
};

constexpr size_t MAX_PAYLOAD_LEGACY = 1024 * 4;
constexpr size_t MAX_PAYLOAD = 1024 * 1024;

constexpr int VERSION = 0x01000000;

constexpr int MESSAGE_SYNC = parse_message("SYNC");
constexpr int MESSAGE_CNXN = parse_message("CNXN");

struct adb_message
{
	const uint32_t command;
	const uint32_t arg1;
	const uint32_t arg2;
	const uint32_t data_length;
	const uint32_t data_crc32;
	const uint32_t magic = command ^ 0xFFFFFFFF;
};

struct adb_packet
{
	const adb_message msg;
	const std::string payload;
};

class serializer
{

public:
	static std::string serialize(const adb_packet& packet);
	static adb_packet deserialize(const std::string& input);
};

}
}
