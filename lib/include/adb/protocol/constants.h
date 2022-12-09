namespace adb
{
namespace protocol
{

//Why does this method exist? Because readability.
//Also because I love bit shifting lul.
constexpr int command_as_int(const char in[4])
{
	return (in[3]) << 24 |
		(in[2]) << 16 |
		(in[1]) << 8 |
		(in[0]);
};

constexpr size_t MAX_PAYLOAD_LEGACY = 1024 * 4;
constexpr size_t MAX_PAYLOAD = 1024 * 1024;

constexpr int PROTOCOL_VERSION = 0x01000000;

constexpr int COMMAND_SYNC = command_as_int("SYNC");  //0x434e5953
constexpr int COMMAND_CNXN = command_as_int("CNXN");  //0x4e584e43
constexpr int COMMAND_AUTH = command_as_int("AUTH");  //0x48545541
constexpr int COMMAND_STLS = command_as_int("STLS");  //0x534C5453
constexpr int COMMAND_OPEN = command_as_int("OPEN");  //0x4e45504f
constexpr int COMMAND_OKAY = command_as_int("OKAY");  //0x59414b4f
constexpr int COMMAND_WRTE = command_as_int("WRTE");  //0x45545257
constexpr int COMMAND_CLSE = command_as_int("CLSE");   //0x45534c43

}
}