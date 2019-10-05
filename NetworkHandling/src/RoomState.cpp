#include "RoomState.h"
#include <iostream>
#include <cstdlib>

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
	return true;
}

void DefaultRoomState::Tick(float elapsed)
{
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
	std::cout << "Entering visual state" << std::endl;
	s1::ShapeDisplay * display = _visualPart->AddCube(vec3(GetSize(), 0, 0), vec3(1, 1, 1));
	_allShapes[entered] = display;
}

void VisualRoomState::PlayerLeft(Player* left)
{
	std::map<Player*, s1::ShapeDisplay*>::iterator it;
	it = _allShapes.find(left);
	_allShapes.erase(it);
}

bool VisualRoomState::Init()
{
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

void VisualRoomState::Tick(float elapsed)
{
	_visualPart->Update(elapsed);
}