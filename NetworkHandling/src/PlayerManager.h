#pragma once
#include <list>
#include "SFML/Network.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>

#define KEEP_ALIVE "al"
#define DEFAULT_TIMEOUT 5


class PlayerManager
{
	protected:
		std::list<std::pair<sf::TcpSocket*, float>> alivesPlayer;

	public:
		inline void AddPlayer(sf::TcpSocket * input)
		{
			std::cout << "Added" << std::endl;
			alivesPlayer.push_back(std::pair<sf::TcpSocket*, float>(input, DEFAULT_TIMEOUT));
		}

		//Decrease count ,disconnect at 0
		void Update(float elapsed);
		
};