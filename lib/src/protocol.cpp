#include <sstream>
#include "adb/protocol.h"
#include <iostream>

namespace adb
{
namespace protocol
{

payload_t make_payload(const char* _p_payload)
{
	payload_t payload;
	payload.insert(payload.end(), _p_payload, _p_payload + strlen(_p_payload));
	return payload;
}

uint32_t payload_size(const payload_t& payload)
{
	return static_cast<int32_t>(payload.size());
}

const size_t msg_field_size = sizeof(uint32_t);

template<typename Data>
void put_to_buffer(std::stringbuf& buffer, Data& data, size_t size)
{
	buffer.sputn(reinterpret_cast<const char*>(&data), size);
}

template<typename Data>
Data read_from_buffer(std::stringbuf& buffer, size_t size)
{
	Data dest;
	buffer.sgetn(reinterpret_cast<char*>(&dest), size);
	return dest;
}

adb_packet serializer::deserialize(const std::string& input)
{
	std::stringbuf buffer(input);

	adb_message message;
	adb_packet packet;

	message.command = read_from_buffer<uint32_t>(buffer, msg_field_size);
	message.arg1 = read_from_buffer<uint32_t>(buffer, msg_field_size);
	message.arg2 = read_from_buffer<uint32_t>(buffer, msg_field_size);
	message.data_length = read_from_buffer<uint32_t>(buffer, msg_field_size);
	message.data_crc32 = read_from_buffer<uint32_t>(buffer, msg_field_size);
	message.magic = read_from_buffer<uint32_t>(buffer, msg_field_size);

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
