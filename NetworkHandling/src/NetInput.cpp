#include "NetInput.h"
#include <iostream>

void NetInput::Update(double elapsed)
{
	PlayerPacket* packet = _buffer->Pop();
	if (packet != nullptr)
	{
		std::cout << packet->content << std::endl;
		if (packet->content == CONNECT_KEY && _lobby.RequestEnter(packet->player))
		{
			packet->player->ChangePlace(&_lobby);
		}
		else if (packet->content == CREATE_ROOM)
		{
			Room* rm = _lobby.CreateRoom(2);
			if (rm->RequestEnter(packet->player))
			{
				packet->player->ChangePlace(rm);
			}
		}
		else
		{
			Command cmd = GenerateCommand(packet);
			packet->player->AddCommand(cmd);
		}
	}
}

NetInput::NetInput(PlayerManager* pM, PacketBuffer * buffer)
{
	_pM = pM;
	_buffer = buffer;
}

Command NetInput::GenerateCommand(PlayerPacket* pp)
{
	Command cmd;
	string typeCmd = pp->content.substr(0, 2);
	cmd.player = pp->player;

	//To change
	if (typeCmd == "MV")
	{
		cmd.cmdType = CommandType::MOVE;
	}

	std::vector<std::string> splitted = Consts::Split(pp->content, '#');
	int count = 0;
	bool ignoreFirst = true;

	for (string value : splitted)
	{
		if (ignoreFirst)
		{
			ignoreFirst = false;
			continue;
		}
		cmd.params[count] = std::stod(value);
		std::cout << cmd.params[count] << std::endl;
		count++;
	}
	return cmd;
}