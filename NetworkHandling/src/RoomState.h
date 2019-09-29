#pragma once
#include <list>
#include "Player.h"

class RoomState
{
	protected:
		bool _isInit;
		std::list<Player*> _players;

	public:
		virtual void PlayerEntered(Player* entered) = 0;
		virtual void PlayerLeft(Player* left) = 0;
		virtual bool Init() = 0;
		virtual bool UnInit() = 0;
		virtual void Update(float elapsed) = 0;
		inline bool GetIsInit() { return _isInit; }
		inline unsigned int GetSize() { return _players.size(); }
};

class DefaultRoomState : public RoomState
{
	public :
		virtual void PlayerEntered(Player* entered);
		virtual void PlayerLeft(Player* left);
		virtual bool Init();
		virtual bool UnInit();
		virtual void Update(float elapsed);
};