#include "adb/protocol/util.h"

namespace adb
{
namespace protocol
{

adb_packet make_packet(
	const adb_command command,
	const uint32_t arg1,
	const uint32_t arg2,
	const char* _p_payload
) {
	uint32_t ucommand = static_cast<uint32_t>(command);
	payload_t payload = make_payload(_p_payload);
	adb_message message {
		ucommand,
		arg1,
		arg2,
		payload_size(payload),
		0,
		ucommand ^ 0xFFFFFFFF
	};
	adb_packet packet {
		message,
		payload
	};
	return packet;
};

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

std::ostream& operator<<(std::ostream& os, const adb::protocol::adb_packet& packet)
{
	os << "{ {" << packet.msg.command << ", " << packet.msg.arg1 << ", " << packet.msg.arg2
		<< ", " << packet.msg.data_length << ", " << packet.msg.data_crc32 << ", "
		<< packet.msg.magic << "}, " << '"';

	for (const char& c : packet.payload)
	{
		os << c;
	}

	os << '"' << "}";

	return os;
}


}
}