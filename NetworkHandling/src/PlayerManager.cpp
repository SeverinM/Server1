#pragma once
#include "PlayerManager.h"
#include <sstream>

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

	int tempId;
	if (_idRecycle.size() == 0)
		tempId = PlayerManager::_ID++;
	else
	{
		tempId = _idRecycle.top();
		_idRecycle.pop();
	}
	tempId = 15;

	_alivesPlayer[tempId] = player;

	PlayerPacket* pp = new PlayerPacket();
	pp->protocol = NetworkProtocol::TCP;
	pp->idPlayer = tempId;
	pp->port = sock->getLocalPort();
	pp->receivedAt = 0;
	pp->sentAt = 0;
	pp->content = CONNECT_KEY;
	_packets.push(pp);
	std::stringstream ss;
	ss << std::hex << tempId;
	sock->send(ss.str().c_str(), 100);
}

void PlayerManager::RemovePlayer(int id)
{
	std::map<int,  Player* >::iterator it;
	it = _alivesPlayer.find(id);
	if (it != _alivesPlayer.end())
	{
		it->second->Kill();
		_alivesPlayer.erase(it);
		_idRecycle.push(id);
	}
}

Player* PlayerManager::FindPlayer(int id)
{
	std::map<int, Player* >::iterator it;
	it = _alivesPlayer.find(id);
	if (it != _alivesPlayer.end())
	{
		return it->second;
	}
	return nullptr;
}
