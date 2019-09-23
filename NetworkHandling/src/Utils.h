#pragma once
#include "SFML/Network.hpp"
#include <string>

using namespace std;

#define PACKET_SIZE 100
#define KEEP_ALIVE "al"
#define DEFAULT_TIMEOUT 10

class Utils
{

};

enum NetworkProtocol
{
	UDP = 0,
	TCP
};

struct PlayerPacket
{
	sf::IpAddress from;
	string content;
	long sentAt;
	long receivedAt;
	NetworkProtocol protocol;
};
