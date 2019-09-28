#include "SFML/Network.hpp"
#include <thread>
#include <chrono>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	int id;
	string ip;
	std::cin >> ip;

	sf::TcpSocket sock;
	sf::UdpSocket sockUdp;
	sockUdp.bind(54000);
	std::cout << "Connecting at " << ip << std::endl;
	sock.connect(ip, 54000);
	std::cout << "connected" << std::endl;
	char data[100];
	size_t received;
	sock.receive(data, 100, received);
	std::cout << data << std::endl;
	char dataId[20];
	memcpy(dataId, &data[0], 6);

	std::cout << dataId << std::endl;

	char alive = 'a';
	while (sock.send(&alive, 1)) { std::this_thread::sleep_for(std::chrono::milliseconds(500)); }

	std::cin >> ip;

	return 0;
}