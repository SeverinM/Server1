#pragma once
#include <list>
#include "SFML/Network.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "Utils.h"
#include <queue>

//Keep a tcp flux of connected players
class PlayerManager
{
	protected:
		std::list<std::pair<sf::TcpSocket*, float>> _alivesPlayer;
		queue<PlayerPacket*> packets;

	public:
		inline void AddPlayer(sf::TcpSocket * input)
		{
			_alivesPlayer.push_back(std::pair<sf::TcpSocket*, float>(input, DEFAULT_TIMEOUT));			
		}

		PlayerPacket* GetNextPacket();

		//Decrease count ,disconnect at 0
		void Update(float elapsed);
		bool IsConnected(sf::IpAddress from);
};