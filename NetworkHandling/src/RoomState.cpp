#include "RoomState.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <sstream>

void RoomState::ChangeState(RoomState* newState)
{
	Player* player = Pop();
	while (player != NULL)
	{
		PlayerLeft(player);
		newState->PlayerEntered(player);
	}
}


/**
DefaultRoomState -- Does nothing by itself
**/
void DefaultRoomState::PlayerEntered(Player* entered)
{
	std::cout << "Entering default state" << std::endl;
	_players.push_back(entered);
}

void DefaultRoomState::PlayerLeft(Player* entered)
{
	std::list<Player*>::iterator it = std::find(_players.begin(), _players.end(), entered);
	if (it != _players.end())
	{
		_players.erase(it);
	}
}

bool DefaultRoomState::UnInit()
{
	return true;
}

bool DefaultRoomState::Init()
{
	_epochMilliStart = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
	return true;
}

Player * DefaultRoomState::Pop()
{
	if (_players.size() == 0)
		return NULL;

	Player* player = _players.back();
	_players.pop_back();
	return player;
}

/**
	VisualRoomState -- Create a visual representation of the game state
**/

void VisualRoomState::PlayerEntered(Player* entered)
{
	s1::ShapeDisplay * display = _visualPart->AddCube(vec3(GetSize(), 0, 0), vec3(1, 1, 1));
	_allShapes[entered] = display;
	std::ostringstream oss;
	oss << "STRT" << _epochMilliStart;
	entered->Send(oss.str().c_str(), oss.str().size(), NetworkProtocol::UDP);
}

void VisualRoomState::PlayerLeft(Player* left)
{
	std::map<Player*, s1::ShapeDisplay*>::iterator it;
	it = _allShapes.find(left);
	_allShapes.erase(it);
}

bool VisualRoomState::Init()
{
	_epochMilliStart = Consts::lastTick;
	_visualPart = new s1::Instance(800, 600);
	_visualPart->Init("../WorldVisual/src/shader");
	_isInit = true;
	return true;
}

bool VisualRoomState::UnInit()
{
	delete _visualPart;
	_isInit = false;
	return true;
}

Player* VisualRoomState::Pop()
{
	if (_allShapes.empty())
	{
		return NULL;
	}
	std::map<Player*, s1::ShapeDisplay*>::iterator it = _allShapes.end();
	Player* output = it->first;
	_allShapes.erase(it);
	return output;
}

void VisualRoomState::Tick()
{
	_visualPart->Update(Consts::deltaTick);
}

void VisualRoomState::InterpretCommand(Command command)
{
	std::map<Player*, s1::ShapeDisplay*>::iterator it = _allShapes.find(command.player);
	it->second->SetPosition(vec3(command.params[0], command.params[1], command.params[2]), true);
}