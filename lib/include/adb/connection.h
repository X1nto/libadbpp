#pragma once

#include "transport.h"

namespace adb
{

class connection
{
private:
	transport adb_connector;

public:
	void open(transport& transport);
	void close();

};

}

