#include "NetFix.h"
#include <iostream>
#include <string>

NetFix* NetFix::_instance = nullptr;

NetFix* NetFix::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new NetFix();
	}

	return _instance;
}

void NetFix::Init(int port, PlayerManager * man)
{
	_socket.setBlocking(false);
	_listener.setBlocking(false);
	Socket::Status st(_listener.listen(port));
	if (_socket.bind(port) == Socket::Done && _listener.listen(port) == Socket::Done)
	{
		_isInit = true;
		_port = port;
		_manager = man;
	}
}

void NetFix::Update()
{
	std::size_t received;
	char data[100];
	unsigned short port;
	IpAddress sender;

	if (_socket.receive(data, 100, received,sender,port) == Socket::Done)
	{
		std::cout << std::string(data).substr(0, received) << std::endl;
	}

	//Someone accepted ?
	TcpSocket* client = new TcpSocket();
	if (_listener.accept(*client) == Socket::Done)
	{
		client->setBlocking(false);
		_manager->AddPlayer(client);
	}
}