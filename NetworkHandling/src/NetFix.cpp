#include "NetFix.h"
#include <iostream>
#include <string>
#include "Utils.h"

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
		std::cout << "Init at " << port << std::endl;
	}
}

void NetFix::Update()
{
	std::size_t received;
	char data[PACKET_SIZE];
	unsigned short port;
	IpAddress sender;

	if (_socket.receive(data, PACKET_SIZE, received,sender,port) == Socket::Done)
	{
		if (_manager->IsConnected(sender))
		{
			PlayerPacket* packet = new PlayerPacket();
			packet->from = sender;
			packet->receivedAt = 0;
			packet->sentAt = 0;
			packet->content = std::string(data).substr(0, received);
			packet->protocol = NetworkProtocol::UDP;
			AddPacket(packet);
		}
	}

	//Someone accepted ?
	TcpSocket* client = new TcpSocket();
	if (_listener.accept(*client) == Socket::Done)
	{
		client->setBlocking(false);
		_manager->AddPlayer(client);
	}
}

PlayerPacket* NetFix::GetNextPacket()
{
	if (_packetBuffer.size() == 0)
		return nullptr;

	PlayerPacket* output = _packetBuffer.front();
	_packetBuffer.pop();
	return output;
}