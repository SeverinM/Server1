#pragma once
#include "SFML/Network.hpp"
#include <string>
#include <list>
#include "PlayerPlace.h"
#include <algorithm>
#include "Utils.h"

//forward declaration
struct PlayerPacket;
class PlayerPlace;

enum NetworkProtocol;

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
		PlayerPlace* _place = NULL;
		PlayerState _state = PlayerState::InServer;

	public:
		Player(sf::TcpSocket* sock);
		inline const sf::TcpSocket * const getSocket() { return _connection; }
		inline PlayerState GetPlayerState() {return _state; }
		inline void SetPlayerState(PlayerState newState) { _state = newState; }
		bool TimeoutUpdate(float elapsed);
		PlayerPacket* GetNextReceivedPacket();
		void ResetTimeout();
		void Send(const char* data, unsigned int size, NetworkProtocol protocol);
		void ChangePlace(PlayerPlace* pp);
		~Player();
};