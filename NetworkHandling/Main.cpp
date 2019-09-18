#include "SFML/Network.hpp"

int main()
{
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("192.168.0.5", 53000);
	return 0;
}