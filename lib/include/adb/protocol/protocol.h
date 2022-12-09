#pragma once

#include <string>
#include <vector>

namespace adb
{
namespace protocol
{

using payload_t = std::vector<char>;

struct adb_message
{
	uint32_t command;
	uint32_t arg1;
	uint32_t arg2;
	uint32_t data_length;
	uint32_t data_crc32;
	uint32_t magic;
};

struct adb_packet
{
	adb_message msg;
	payload_t payload;
};

}
}
