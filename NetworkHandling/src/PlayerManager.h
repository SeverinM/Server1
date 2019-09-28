#pragma once
#include <map>
#include "SFML/Network.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "Utils.h"
#include <queue>
#include "Player.h"
#include <stack>

//Keep a tcp flux of connected players
class PlayerManager
{
	private:
		static PlayerManager* _instance;
		PlayerManager();

	protected:
		std::map<unsigned int, Player*> _alivesPlayer;
		queue<PlayerPacket*> _packets;
		static int _ID;

	public:
		void AddPlayer(sf::TcpSocket* sock);
		void RemovePlayer(unsigned int id);
		PlayerPacket* GetNextPacket();
		void Update(float elapsed);
		bool IsConnected(sf::IpAddress from);
		Player* FindPlayer(unsigned int id);
		void Kill(unsigned int id);
		void Kill(std::map<unsigned int, Player*>::iterator it);
		static PlayerManager* GetInstance();
};