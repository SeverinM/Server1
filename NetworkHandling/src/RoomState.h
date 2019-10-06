#pragma once
#include <list>
#include "Player.h"
#include "Instance.h"
#include "ShapeDisplay.h"
#include <map>

class RoomState
{
	protected:
		bool _isInit;
		unsigned long _tick = 0;
		long long _epochMilliStart;

	public:
		virtual void PlayerEntered(Player* entered) = 0;
		virtual void PlayerLeft(Player* left) = 0;
		virtual bool Init() = 0;
		virtual bool UnInit() = 0;
		virtual unsigned int GetSize() = 0;
		virtual void InterpretCommand(Command command) = 0;
		virtual Player* Pop() = 0;
		inline bool GetIsInit() { return _isInit; }
		virtual void Tick() = 0;
		void ChangeState(RoomState* newState);
};

class DefaultRoomState : public RoomState
{
	protected:
		std::list<Player*> _players;

	public :
		virtual void PlayerEntered(Player* entered);
		virtual void PlayerLeft(Player* left);
		virtual bool Init();
		virtual bool UnInit();
		virtual Player* Pop();
		void InterpretCommand(Command command) {};
		inline virtual unsigned int GetSize() { return _players.size(); }
};

class VisualRoomState : public RoomState
{
	private:
		s1::Instance* _visualPart;
		std::map<Player*, s1::ShapeDisplay*> _allShapes;

	public:
		virtual Player* Pop();
		virtual void PlayerEntered(Player* entered);
		virtual void PlayerLeft(Player* left);
		virtual bool Init();
		virtual bool UnInit();
		virtual void Tick();
		void InterpretCommand(Command command);
		inline virtual unsigned int GetSize() { return _allShapes.size(); }
};