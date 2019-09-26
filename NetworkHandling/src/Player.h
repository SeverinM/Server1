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
		int _id;

	public:
		Player(sf::TcpSocket* sock);
		inline const sf::TcpSocket * const getSocket() { return _connection; }
		inline int GetId() const { return _id; }
		bool TimeoutUpdate(float elapsed);
		PlayerPacket* GetNextReceivedPacket();
		void AddObserver(PlayerObservable* obs);
		void RemoveObserver(PlayerObservable* obs);
		void ResetTimeout();
		void Kill();
		bool operator<(const Player &player);
};