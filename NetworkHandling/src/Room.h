#pragma once
#include "Player.h"
#include "PlayerObservable.h"
#include <unordered_map>

class Room : public PlayerPlace
{
	protected:
		unsigned int _maxPlayer;
		unsigned int _id;
		std::list<Player *> _playersInRoom;
		static unsigned int _ID;

	public :
		Room(unsigned int nbPlayers);
		inline unsigned int GetId() { return _id; }
		bool RequestEnter(Player * player) override;
		void PlayerLeft( Player * player) override;
		void PlayerEnter( Player* player) override;
};