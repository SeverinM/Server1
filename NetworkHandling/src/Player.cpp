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

void Player::AddObserver(PlayerObservable* obs)
{
	observers.push_back(obs);
}

void Player::RemoveObserver(PlayerObservable* obs)
{
	std::list<PlayerObservable*>::iterator it = std::find(observers.begin(), observers.end(), obs);
	if (it != observers.end())
	{
		observers.erase(it);
	}
}

void Player::ResetTimeout()
{
	_timeout = DEFAULT_TIMEOUT;
}

void Player::NotifyLeave(unsigned int id)
{
	_connection->disconnect();
	std::list<PlayerObservable*>::iterator it;
	//Unsub everyone on disconnect
	for (it = observers.begin(); it != observers.end(); it++)
	{
		(*it)->PlayerLeft(id);
	}
}