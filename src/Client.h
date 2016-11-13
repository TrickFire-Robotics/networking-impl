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

	void SetMessageCallback(void (*msgCallback)(Packet&));

	void Join();

private:
	std::string address;
	int port;
	TcpSocket socket;
	pthread_t messageThread;

	void (*msgCallback)(Packet&);

	int Connect();

	void StartMessageThread();
	static void * _MessageLoopWrapper(void * client);
	void * MessageListeningLoop();
};
}

#endif /* CLIENT_H_ */
