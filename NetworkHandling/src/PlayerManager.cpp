#pragma once
#include "PlayerManager.h"
#include <string>

using namespace sf;

int PlayerManager::_ID = 0;

void PlayerManager::Update(float elapsed)
{
	if (_alivesPlayer.size() == 0)
	{
		return;
	}

	std::map<int, Player *>::iterator it = _alivesPlayer.begin();
	while (_alivesPlayer.size() > 0 && it != _alivesPlayer.end())
	{
		Player* plyr = it->second;

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
			_packets.push(pp);
		}
	}
}

bool PlayerManager::IsConnected(sf::IpAddress from)
{
	return false;
}

PlayerPacket* PlayerManager::GetNextPacket()
{
	if (_packets.size() == 0)
		return nullptr;

	PlayerPacket* pp = _packets.front();
	_packets.pop();
	return pp;
}

void PlayerManager::AddPlayer(sf::TcpSocket* sock)
{
	std::cout << "New Player" << std::endl;
	Player* player = new Player(sock);
	_alivesPlayer[PlayerManager::_ID] = player;

	PlayerPacket* pp = new PlayerPacket();
	pp->protocol = NetworkProtocol::TCP;
	pp->idPlayer = PlayerManager::_ID;
	pp->port = sock->getLocalPort();
	pp->receivedAt = 0;
	pp->sentAt = 0;
	pp->content = CONNECT_KEY;
	_packets.push(pp);
	string data = std::to_string(PlayerManager::_ID);
	PlayerManager::_ID++;
	sock->send(data.c_str(), 100);
}

void PlayerManager::RemovePlayer(Player* player)
{
	/*std::map<int,  Player* > ::iterator it;
	it = std::find(_alivesPlayer.begin(), _alivesPlayer.end(), player);
	if (it != _alivesPlayer.end())
	{
		it->second->Kill();
		_alivesPlayer.erase(it);
	}*/
}
