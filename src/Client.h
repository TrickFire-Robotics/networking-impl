#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

using namespace sf;

namespace trickfire {

class Client {
public:
	Client(std::string address);
	Client(std::string address, int port);

	int Send(Packet& packet);
	void Disconnect();

	void SetMessageCallback(void (*msgCallback)(Packet&));

	void Join();

private:
	std::string address;
	int port;
	TcpSocket socket;
	Thread sfmlMessageThread;

	void (*msgCallback)(Packet&);

	int Connect();

	void SfmlMessageListeningLoop();
};
}

#endif
