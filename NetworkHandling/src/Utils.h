#pragma once
#include "SFML/Network.hpp"
#include <string>
#include "Player.h"

using namespace std;

#define PACKET_SIZE 100
#define KEEP_ALIVE "al"
#define DEFAULT_TIMEOUT 100
#define SERVER_FREQUENCY 2.0
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

struct PlayerPacket
{
	Player* player;
	string content;
	long sentAt;
	long receivedAt;
	NetworkProtocol protocol;
	short port = 0;
};