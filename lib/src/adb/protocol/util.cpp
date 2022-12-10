#include "adb/protocol/util.h"
#include <string>

namespace adb
{
namespace protocol
{

std::string systype_string(adb_system_identity_systype system_type)
{
	switch (system_type)
	{
	case adb_system_identity_systype::bootloader:
		return "bootloader";
	case adb_system_identity_systype::device:
		return "device";
	case adb_system_identity_systype::host:
		return "host";
	}
}

adb_packet make_packet(
	const adb_command command,
	const uint32_t arg1,
	const uint32_t arg2,
	const std::string& _p_payload
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

adb_packet make_connect_packet(
	const adb_system_identity_systype system_type,
	const std::string& serial_no,
	const std::string& banner) 
{
	return make_packet(
		adb_command::connect,
		PROTOCOL_VERSION,
		MAX_PAYLOAD_LEGACY,
		systype_string(system_type) + ':' + serial_no + ':' + banner
	);
}

payload_t make_payload(const std::string& _p_payload)
{
	payload_t payload;
	payload.insert(payload.end(), _p_payload.begin(), _p_payload.end());
	return payload;
}

uint32_t payload_size(const payload_t& payload)
{
	return static_cast<int32_t>(payload.size());
}

std::ostream& operator<<(std::ostream& os, const adb_message& message)
{
	os << '{' << message.command << ',' << message.arg1 << ',' << message.arg2
		<< ',' << message.data_length << ',' << message.data_crc32 << ','
		<< message.magic << '}';
	return os;
}

std::ostream& operator<<(std::ostream& os, const adb::protocol::adb_packet& packet)
{
	os << '{' << packet.msg << ',' << '"';
	for (const char& c : packet.payload)
	{
		os << c;
	}
	os << "\"}";
	return os;
}

}
}