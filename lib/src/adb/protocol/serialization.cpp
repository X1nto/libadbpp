#include <sstream>
#include "adb/protocol/serialization.h"

namespace adb
{
namespace protocol
{

const size_t msg_field_size = sizeof(uint32_t);

template<typename Data>
void put_to_buffer(std::stringbuf& buffer, Data& data, size_t size)
{
	buffer.sputn(reinterpret_cast<const char*>(&data), size);
}

template<typename Data>
void read_from_buffer(std::stringbuf& buffer, Data& dest, size_t size)
{
	buffer.sgetn(reinterpret_cast<char*>(&dest), size);
}

adb_packet serializer::deserialize(const std::string& input)
{
	std::stringbuf buffer(input);

	adb_message message {};
	adb_packet packet {};

	read_from_buffer(buffer, message.command, msg_field_size);
	read_from_buffer(buffer, message.arg1, msg_field_size);
	read_from_buffer(buffer, message.arg2, msg_field_size);
	read_from_buffer(buffer, message.data_length, msg_field_size);
	read_from_buffer(buffer, message.data_crc32, msg_field_size);
	read_from_buffer(buffer, message.magic, msg_field_size);

	packet.msg = message;

	if (message.data_length > 0)
	{
		for (uint32_t i = 0; i < message.data_length; i++)
		{
			packet.payload.push_back(buffer.sbumpc());
		}
	}

	return packet;
};

std::string serializer::serialize(const adb_packet& packet)
{
	std::stringbuf buffer;
	put_to_buffer(buffer, packet.msg.command, msg_field_size);
	put_to_buffer(buffer, packet.msg.arg1, msg_field_size);
	put_to_buffer(buffer, packet.msg.arg2, msg_field_size);
	put_to_buffer(buffer, packet.msg.data_length, msg_field_size);
	put_to_buffer(buffer, packet.msg.data_crc32, msg_field_size);
	put_to_buffer(buffer, packet.msg.magic, msg_field_size);

	if (packet.payload.size() > 0)
	{
		for (const char& c : packet.payload)
		{
			buffer.sputc(c);
		}
	}

	return buffer.str();
};


}
}