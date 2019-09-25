#pragma once
#include <list>
#include "SFML/Network.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "Utils.h"
#include <queue>
#include "Player.h"

//Keep a tcp flux of connected players
class PlayerManager
{
	protected:
		std::list<Player *> _alivesPlayer;
		queue<PlayerPacket*> packets;

	public:
		void AddPlayer(sf::TcpSocket* sock);
		PlayerPacket* GetNextPacket();
		void Update(float elapsed);
		bool IsConnected(sf::IpAddress from);
};