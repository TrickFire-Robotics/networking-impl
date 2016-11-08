#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <SFML/Network.hpp>

using namespace sf;

namespace trickfire {

class Client {
public:
	Client(std::string address);
	Client(std::string address, int port);

	int Send(Packet& packet);
	void Disconnect();

	int operator<<(Packet& packet);

private:
	std::string address;
	int port;
	TcpSocket socket;

	int Connect();
};
}

#endif /* CLIENT_H_ */
