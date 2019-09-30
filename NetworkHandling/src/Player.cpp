#include "Player.h"
#include <iostream>
#include "NetFix.h"

Player::Player(sf::TcpSocket* sock)
{
	_connection = sock;
	_timeout = DEFAULT_TIMEOUT;
}

Player::~Player()
{
	_connection->disconnect();
	_place = NULL;
}

bool Player::TimeoutUpdate(float elapsed)
{
	_timeout -= elapsed;
	if (_timeout <= 0)
	{
		ResetTimeout();
		return true;
	}
	return false;
}

PlayerPacket* Player::GetNextReceivedPacket()
{
	char data[100];
	size_t sizeReceived;
	if (_connection->receive(data, 100, sizeReceived) == sf::Socket::Done)
	{
		PlayerPacket* pp = new PlayerPacket();
		pp->content = std::string(data).substr(0, sizeReceived);
		pp->protocol = NetworkProtocol::TCP;
		pp->receivedAt = 0;
		pp->sentAt = 0;
		return pp;
	}

	return nullptr;
}

void Player::ResetTimeout()
{
	_timeout = DEFAULT_TIMEOUT;
}

void Player::Send(const char* toSend, unsigned int size, NetworkProtocol protocol)
{
	if (protocol == NetworkProtocol::TCP)
		_connection->send(toSend, size);
	else
	{
		std::cout << _connection->getRemoteAddress() << std::endl;
		NetFix::GetInstance()->Send(_connection->getRemoteAddress(), toSend, size);
	}
}

void Player::ChangePlace(PlayerPlace* pp)
{
	if (_place != NULL)
	{
		_place->PlayerLeft(this);
	}

	if (pp != NULL)
	{
		pp->PlayerEnter(this);
	}
	else
	{
		_connection->disconnect();
	}

	_place = pp;
}