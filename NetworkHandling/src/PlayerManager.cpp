#pragma once
#include "PlayerManager.h"
#include <string>

using namespace sf;

class NetFix;

void PlayerManager::Update(float elapsed)
{
	if (_alivesPlayer.size() == 0)
	{
		return;
	}

	std::list<std::pair<TcpSocket*, float>>::iterator it = _alivesPlayer.begin();
	for (; it != _alivesPlayer.end() ;)
	{
		it->second -= elapsed;
		if ((*it).second <= 0)
		{
			TcpSocket* sock = it->first;
			sock->disconnect();
			it = _alivesPlayer.erase(it);
			delete sock;
		}
		else
		{
			char data[100];
			std::size_t received;
			if ((*it).first->receive(data, 100, received) == Socket::Done)
			{
				(*it).second = DEFAULT_TIMEOUT;
				PlayerPacket* pp = new PlayerPacket();
				pp->content = std::string(data).substr(0, received);
				pp->from = it->first->getRemoteAddress();
				pp->protocol = NetworkProtocol::TCP;
				pp->receivedAt = 0;
				pp->sentAt = 0;
				packets.push(pp);
			}
			++it;
		}
	}
}

bool PlayerManager::IsConnected(sf::IpAddress from)
{
	std::list<std::pair<TcpSocket*, float>>::iterator it = _alivesPlayer.begin();
	for (; it != _alivesPlayer.end();)
	{
		if (from == it->first->getRemoteAddress())
			return true;
	}
	return false;
}

PlayerPacket* PlayerManager::GetNextPacket()
{
	if (packets.size() == 0)
		return nullptr;

	PlayerPacket* pp = packets.front();
	packets.pop();
	return pp;
}
