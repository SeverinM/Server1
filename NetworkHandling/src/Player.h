#pragma once
#include "SFML/Network.hpp"
#include <string>
#include <list>
#include "PlayerObservable.h"
#include <algorithm>
#include "Utils.h"

//forward declaration
class PlayerPacket;
class PlayerObservable;

class Player
{
	private:
		sf::TcpSocket* _connection;
		float _timeout;
		std::list<PlayerObservable*> observers;

	public:
		Player(sf::TcpSocket* sock);
		inline const sf::TcpSocket * const getSocket() { return _connection; }
		bool TimeoutUpdate(float elapsed);
		PlayerPacket* GetNextReceivedPacket();
		void AddObserver(PlayerObservable* obs);
		void RemoveObserver(PlayerObservable* obs);
		void ResetTimeout();
		void Kill();
};