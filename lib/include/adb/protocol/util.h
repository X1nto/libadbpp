#include <iostream>
#include <string>

#include "constants.h"
#include "protocol.h"

#if __cplusplus >= 202002L
#define _CONSTEXPR_20 constexpr
#else
#define _CONSTEXPR_20
#endif

namespace adb
{
namespace protocol
{

enum class adb_command
{
	connect = COMMAND_CNXN,
	sync = COMMAND_SYNC,
	auth = COMMAND_AUTH,
	stls = COMMAND_STLS,
	open = COMMAND_OPEN,
	okay = COMMAND_OKAY,
	write = COMMAND_WRTE,
	close = COMMAND_CLSE
};

enum class adb_system_identity_systype
{
	bootloader, device, host
};

adb_packet make_packet(
	const adb_command command,
	const uint32_t arg1,
	const uint32_t arg2,
	const std::string& _p_payload
);
adb_packet make_connect_packet(
	const adb_system_identity_systype system_type,
	const std::string& serial_no,
	const std::string& banner
);
adb_packet make_sync_packet();
adb_packet make_auth_packet();
adb_packet make_stls_packet();
adb_packet make_open_packet();
adb_packet make_okay_packet();
adb_packet make_write_packet();
adb_packet make_close_packet();

_CONSTEXPR_20 payload_t make_payload(const std::string& _p_payload);

_CONSTEXPR_20 uint32_t payload_size(const payload_t& payload);

std::ostream& operator<<(std::ostream& os, const adb_message& packet);
std::ostream& operator<<(std::ostream& os, const adb_packet& packet);

}
}