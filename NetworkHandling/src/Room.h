#pragma once
#include "Player.h"
#include "PlayerObservable.h"
#include <unordered_map>

class Room : public PlayerObservable
{
	protected:
		unsigned int _maxPlayer;
		unsigned int _id;
		std::list<unsigned int> _playersInRoom;
		static unsigned int _ID;

	public :
		Room(unsigned int nbPlayers);
		void AddPlayer(unsigned int id);
		void RequestEnter(unsigned int id);
		inline unsigned int GetId() { return _id; }
		void PlayerLeft(unsigned int plyr);
};