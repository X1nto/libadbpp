#include <string>
#include "protocol.h"

namespace adb
{
namespace protocol
{

class serializer
{

public:
	static std::string serialize(const adb_packet& packet);
	static adb_packet deserialize(const std::string& input);
};

}
}