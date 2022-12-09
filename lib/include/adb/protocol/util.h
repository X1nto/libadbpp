#include <iostream>

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
	SYNC = COMMAND_SYNC,
	CNXN = COMMAND_CNXN,
	AUTH = COMMAND_AUTH,
	STLS = COMMAND_STLS,
	OPEN = COMMAND_OPEN,
	OKAY = COMMAND_OKAY,
	WRTE = COMMAND_WRTE,
	CLSE = COMMAND_CLSE
};

adb_packet make_packet(
	const adb_command command,
	const uint32_t arg1,
	const uint32_t arg2,
	const char* _p_payload
);

_CONSTEXPR_20 payload_t make_payload(const char* _p_payload);
_CONSTEXPR_20 uint32_t payload_size(const payload_t& payload);

std::ostream& operator<<(std::ostream& os, const adb::protocol::adb_packet& packet);

}
}