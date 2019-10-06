#include "NetFix.h"
#include <iostream>
#include <string>
#include "Utils.h"
#include <sstream>

NetFix* NetFix::_instance = nullptr;

NetFix* NetFix::GetInstance()
{
	return _instance;
}

void NetFix::Init(int port, PlayerManager * man)
{
	_socket.setBlocking(false);
	_listener.setBlocking(false);
	Socket::Status st(_listener.listen(port));
	if (_socket.bind(port + 1) == Socket::Done && _listener.listen(port) == Socket::Done)
	{
		_isInit = true;
		_port = port;
		_manager = man;
		std::cout << "Init at " << port << std::endl;
	}
	_instance = this;
}

void NetFix::Update()
{
	std::size_t received;
	char data[PACKET_SIZE];
	unsigned short port;
	IpAddress sender;

	if (_socket.receive(data, PACKET_SIZE, received,sender,port) == Socket::Done)
	{
		PlayerPacket* packet = new PlayerPacket();
		packet->content = std::string(data).substr(BYTES_ID * 2, received - (BYTES_ID * 2));
		packet->protocol = NetworkProtocol::UDP;

		//Parse the id
		char idSample[BYTES_ID * 2];
		memcpy(idSample, &data[0], BYTES_ID * 2);
		unsigned int id = std::stoul(idSample, nullptr, 16);

		//Let pass only if a player exist
		Player* player = _manager->FindPlayer(id);
		if (player != nullptr)
		{
			packet->player = player;
			player->ResetTimeout();
			_buffer->Insert(packet);
		}
		else
		{
			std::cout << "Rejected" << std::endl;
			delete packet;
		}
	}

	//Someone accepted ?
	TcpSocket* client = new TcpSocket();
	if (_listener.accept(*client) == Socket::Done)
	{
		std::cout << "Accept : " << client->getRemoteAddress() << std::endl;
		client->setBlocking(false);
		_manager->AddPlayer(client);
	}
}

void NetFix::Send(sf::IpAddress addr, const char* data, unsigned int size)
{
	_socket.send(data, size, addr, DEFAULT_PORT + 1);
}