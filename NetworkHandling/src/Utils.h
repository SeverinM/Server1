#pragma once
#include "SFML/Network.hpp"
#include <string>
#include <sstream>

using namespace std;

#define PACKET_SIZE 100
#define KEEP_ALIVE "al"
#define DEFAULT_TIMEOUT 5
#define SERVER_FREQUENCY 50;
#define TIMEOUT_MESSAGE "Timeout ! Disconnect"
#define CONNECT_KEY "LBYCONN"
#define BYTES_ID 3
#define CREATE_ROOM "CRTROOM"
#define LEFT_LOBBY "LBYLEFT"
#define DEFAULT_PORT 54000

class Player;

enum NetworkProtocol
{
	UDP = 0,
	TCP
};

struct Consts
{
	static double deltaTick;

	static std::vector<std::string> Split(std::string strToSplit, char delimeter)
	{
		std::stringstream ss(strToSplit);
		std::string item;
		std::vector<std::string> splittedStrings;
		while (std::getline(ss, item, delimeter))
		{
			splittedStrings.push_back(item);
		}
		return splittedStrings;
	}
};

struct PlayerPacket
{
	Player* player;
	string content;
	NetworkProtocol protocol;
	short port = 0;
};