#pragma once
#include "PlayerManager.h"
#include <sstream>

using namespace sf;

int PlayerManager::_ID = 0;
PlayerManager* PlayerManager::_instance = nullptr;

void PlayerManager::Update(double elapsed)
{
	if (_alivesPlayer.size() == 0)
	{
		return;
	}

	std::map<unsigned int, Player *>::iterator it = _alivesPlayer.begin();
	while (_alivesPlayer.size() > 0 && it != _alivesPlayer.end())
	{
		Player* plyr = it->second;

		//Timeout verification
		if (plyr->TimeoutUpdate(elapsed))
		{
			std::cout << plyr->getSocket()->getRemoteAddress() << " disconnected (timeout) " << std::endl;
			Kill(it);
			continue;
		}

		if (plyr->isDisconnected())
		{
			std::cout << plyr->getSocket()->getRemoteAddress() << "disconnected" << std::endl;
			Kill(it);
			continue;
		}
		it++;

		//Received something via TCP
		PlayerPacket* pp = plyr->GetNextReceivedPacket();
		if (pp != nullptr)
		{
			pp->player = plyr;
			plyr->ResetTimeout();
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
	tempId = ++PlayerManager::_ID;
	_alivesPlayer[tempId] = player;
	player->SetId(tempId);
	std::stringstream ss;
	ss << std::hex << tempId;
	ss << "!";
	string idStr = ss.str();
	while (idStr.size() < BYTES_ID * 2)
	{
		idStr.insert(0, "0");
	}
	sock->send(idStr.c_str(), BYTES_ID * 2);
}

void PlayerManager::RemovePlayer(unsigned int id)
{
	std::map<unsigned int,  Player* >::iterator it;
	it = _alivesPlayer.find(id);
	if (it != _alivesPlayer.end())
	{
		Kill(it);
		_alivesPlayer.erase(it);
	}
}

Player* PlayerManager::FindPlayer(unsigned int id)
{
	std::map<unsigned int, Player* >::iterator it;
	it = _alivesPlayer.find(id);
	if (it != _alivesPlayer.end())
	{
		return it->second;
	}
	return nullptr;
}

PlayerManager* PlayerManager::GetInstance()
{
	if (_instance == nullptr)
	{
		return new PlayerManager();
	}
	return _instance;
}

PlayerManager::PlayerManager()
{
	_instance = this;
}

void PlayerManager::Kill(std::map<unsigned int, Player*>::iterator it)
{
	it->second->ChangePlace(NULL);
	delete(it->second);
	_alivesPlayer.erase(it);
}
