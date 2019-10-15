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

	//No one was here before
	if (_allShapes.size() == 1)
	{
		//Notify that the player was created
		oss << "STRT";
		entered->Send(oss.str().c_str(), oss.str().size(), NetworkProtocol::UDP);
	}
	else
	{
		oss << "JOIN" << _tick;
		oss << "#" << entered->GetId();
		oss << "#" << _allShapes[entered]->GetPosition().x;
		oss << "#" << _allShapes[entered]->GetPosition().y;
		oss << "#" << _allShapes[entered]->GetPosition().z;

		//Notify everyone that someone joined
		std::map<Player*, s1::ShapeDisplay*>::iterator it;
		for (it = _allShapes.begin(); it != _allShapes.end(); it++)
		{
			it->first->Send(oss.str().c_str(), oss.str().size(), NetworkProtocol::UDP);
		}
	}
}

void VisualRoomState::PlayerLeft(Player* left)
{
	std::cout << "Left" << std::endl;
	std::map<Player*, s1::ShapeDisplay*>::iterator it;
	it = _allShapes.find(left);
	_visualPart->Delete(it->second);
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
	_tick++;
	_visualPart->Update(Consts::deltaTick);
	std::map<Player*, s1::ShapeDisplay*>::iterator it;
	if (_allShapes.size() == 0)
		return;

	std::stringstream ss;
	ss << _tick;
	ss << "|";
	for (it = _allShapes.begin(); it != _allShapes.end(); it++)
	{
		ss << it->first->GetId();
		ss << "#";
		ss << it->second->GetPosition().x;
		ss << "#";
		ss << it->second->GetPosition().y;
		ss << "#";
		ss << it->second->GetPosition().z;
		ss << "#|";
	}

	for (it = _allShapes.begin(); it != _allShapes.end(); it++)
	{
		it->first->Send(ss.str().c_str(), ss.str().size(), NetworkProtocol::UDP);
	}
}

void VisualRoomState::InterpretCommand(Command command)
{
	std::map<Player*, s1::ShapeDisplay*>::iterator it = _allShapes.find(command.player);
	it->second->SetPosition(vec3(command.params[0], command.params[1], command.params[2]), true);
}