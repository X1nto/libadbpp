#include <sstream>
#include "adb/protocol.h"

namespace adb
{
namespace protocol
{
const size_t msg_field_size = sizeof(uint32_t);

template<typename Data>
void put_data_in_buffer(std::stringbuf& buffer, Data& data, size_t size)
{
	buffer.sputn(reinterpret_cast<const char*>(&data), size);
}

template<typename Data>
void put_data_from_buffer(std::stringbuf& buffer, Data& dest, size_t size)
{
	buffer.sgetn(reinterpret_cast<char*>(&dest), size);
}

adb_packet serializer::deserialize(const std::string& input)
{
	std::stringbuf buffer(input);

	uint32_t command;
	uint32_t arg1;
	uint32_t arg2;
	uint32_t data_length;
	uint32_t data_crc32;
	uint32_t magic;
	put_data_from_buffer(buffer, command, msg_field_size);
	put_data_from_buffer(buffer, arg1, msg_field_size);
	put_data_from_buffer(buffer, arg2, msg_field_size);
	put_data_from_buffer(buffer, data_length, msg_field_size);
	put_data_from_buffer(buffer, data_crc32, msg_field_size);
	put_data_from_buffer(buffer, magic, msg_field_size);
	
	char* payload = new char[data_length];
	if (data_length > 0)
	{
		buffer.sgetn(payload, data_length);
	}

	const adb_message message {command, arg1, arg2, data_length, data_crc32, magic};
	const adb_packet packet {message, std::string(payload)};

	delete[] payload;
	return packet;
};

std::string serializer::serialize(const adb_packet& packet)
{
	const size_t msg_field_size = sizeof(uint32_t);
	const size_t payload_size = packet.payload.size();

	std::stringbuf buffer;
	put_data_in_buffer(buffer, packet.msg.command, msg_field_size);
	put_data_in_buffer(buffer, packet.msg.arg1, msg_field_size);
	put_data_in_buffer(buffer, packet.msg.arg2, msg_field_size);
	put_data_in_buffer(buffer, packet.msg.data_length, msg_field_size);
	put_data_in_buffer(buffer, packet.msg.data_crc32, msg_field_size);
	put_data_in_buffer(buffer, packet.msg.magic, msg_field_size);

	const char* payload_buf = packet.payload.c_str();

	if (payload_size > 0)
	{
		buffer.sputn(payload_buf, payload_size);
	}

	return buffer.str();
};

}
}
