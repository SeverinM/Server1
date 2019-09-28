#pragma once
#include "SFML/Network.hpp"
#include <string>
#include <list>
#include "PlayerObservable.h"
#include <algorithm>
#include "Utils.h"

//forward declaration
struct PlayerPacket;
class PlayerObservable;

enum PlayerState
{
	InLobby,
	InServer,
	InGame,
	InRoom
};


class Player
{
	private:
		sf::TcpSocket* _connection;
		float _timeout;
		std::list<PlayerObservable*> observers;
		PlayerState _state = PlayerState::InServer;

	public:
		Player(sf::TcpSocket* sock);
		inline const sf::TcpSocket * const getSocket() { return _connection; }
		inline PlayerState GetPlayerState() {return _state; }
		inline void SetPlayerState(PlayerState newState) { _state = newState; }
		bool TimeoutUpdate(float elapsed);
		PlayerPacket* GetNextReceivedPacket();
		void AddObserver(PlayerObservable* obs);
		void RemoveObserver(PlayerObservable* obs);
		void ResetTimeout();
		void NotifyLeave(unsigned int id);
};