#pragma once

namespace adb 
{

class transport
{
	virtual void write();
	virtual void bulk_write();
	virtual void read();
	virtual void bulk_read();
};

class usb_transport : public transport {};

class tcp_transport : public transport {};

}