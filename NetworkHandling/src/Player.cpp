#include "Player.h"
#include <iostream>

Player::Player(sf::TcpSocket* sock)
{
	_connection = sock;
	_timeout = DEFAULT_TIMEOUT;
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

void Player::SendUDP(char* toSend, unsigned int size)
{
	sf::UdpSocket* udp = new sf::UdpSocket();
	udp->bind(54000);
	udp->send(toSend, size, _connection->getRemoteAddress(), 54000);
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