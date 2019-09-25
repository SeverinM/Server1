#pragma once
#include "PlayerManager.h"
#include <string>

using namespace sf;

void PlayerManager::Update(float elapsed)
{
	if (_alivesPlayer.size() == 0)
	{
		return;
	}

	std::list<Player *>::iterator it = _alivesPlayer.begin();
	while (_alivesPlayer.size() > 0 && it != _alivesPlayer.end())
	{
		Player* plyr = (*it);

		//Timeout verification
		if (plyr->TimeoutUpdate(elapsed))
		{
			std::cout << plyr->getSocket()->getRemoteAddress() << " disconnected " << std::endl;
			_alivesPlayer.erase(it);
			plyr->Kill();
			delete plyr;
			continue;
		}
		else
		{
			it++;
		}

		PlayerPacket* pp = plyr->GetNextReceivedPacket();
		if (pp != nullptr)
		{
			packets.push(pp);
		}
	}
}

bool PlayerManager::IsConnected(sf::IpAddress from)
{
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

void PlayerManager::AddPlayer(sf::TcpSocket* sock)
{
	Player* player = new Player(sock);
	_alivesPlayer.push_back(player);

	PlayerPacket* pp = new PlayerPacket();
	pp->protocol = NetworkProtocol::TCP;
	pp->from = sock->getRemoteAddress();
	pp->port = sock->getLocalPort();
	pp->receivedAt = 0;
	pp->sentAt = 0;
	pp->content = CONNECT_KEY;
	packets.push(pp);
}
