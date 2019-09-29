#pragma once
#include "Player.h"
#include "PlayerPlace.h"
#include <unordered_map>
#include "RoomState.h"

class Room : public PlayerPlace
{
	protected:
		unsigned int _maxPlayer;
		unsigned int _id;
		static unsigned int _ID;
		RoomState* _roomState;

	public :
		Room(unsigned int nbPlayers);
		inline unsigned int GetId() { return _id; }
		bool RequestEnter(Player * player) override;
		void PlayerLeft( Player * player) override;
		void PlayerEnter( Player* player) override;
};