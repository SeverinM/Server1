#pragma once
#include "SFML/Network.hpp"
#include <string>
#include <list>
#include "PlayerPlace.h"
#include <algorithm>
#include "Utils.h"
#include "Command.h"

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


enum CommandType
{
	MOVE,
	JUMP,
	SHOOT
};

struct Command
{
	float params[4];
	CommandType cmdType;
	Player* player;
};


class Player
{
	private:
		sf::TcpSocket* _connection;
		float _timeout;
		PlayerPlace* _place = NULL;
		PlayerState _state = PlayerState::InServer;
		unsigned int _id;

	public:
		Player(sf::TcpSocket* sock);
		inline const sf::TcpSocket * const getSocket() { return _connection; }
		inline PlayerState GetPlayerState() {return _state; }
		inline void SetPlayerState(PlayerState newState) { _state = newState; }
		inline void SetId(unsigned int id) { _id = id; }
		inline unsigned int GetId() { return _id; }

		void AddCommand(Command command);
		bool TimeoutUpdate(float elapsed);
		PlayerPacket* GetNextReceivedPacket();
		void ResetTimeout();
		void Send(const char* data, unsigned int size, NetworkProtocol protocol);
		void ChangePlace(PlayerPlace* pp);
		~Player();
		std::string GetHexaId();
};