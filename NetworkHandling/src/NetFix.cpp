#include "NetFix.h"

NetFix* NetFix::_instance = nullptr;

NetFix* NetFix::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new NetFix();
	}

	return _instance;
}

void NetFix::Init(int port)
{
	_socket.setBlocking(false);
	if (_socket.bind(port) != Socket::Done)
	{
		//Error
	}
	else
	{
		_isInit = true;
		_port = port;
	}	
}

void NetFix::Update()
{
	std::size_t received;
	char data[100];
	unsigned short port;
	IpAddress sender;

	if (_socket.receive(data, 100, received,sender,port) != Socket::Done)
	{
		//Error
	}
}