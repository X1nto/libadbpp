#pragma once

#include <string>
#include <vector>

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
	uint32_t command;
	uint32_t arg1;
	uint32_t arg2;
	uint32_t data_length;
	uint32_t data_crc32;
	uint32_t magic;
};

using payload_t = std::vector<char>;

struct adb_packet
{
	adb_message msg;
	payload_t payload;
};

#if __cplusplus >= 202002L
constexpr
#endif
payload_t make_payload(const char* _p_payload);
uint32_t payload_size(const payload_t& payload);

class serializer
{

public:
	static std::string serialize(const adb_packet& packet);
	static adb_packet deserialize(const std::string& input);
};

}
}
