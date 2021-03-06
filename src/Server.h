#ifndef SERVER_H_
#define SERVER_H_
#define DEFAULT_PORT 25565

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

using namespace sf;

namespace trickfire {

/**
 * Handles the networking logic for the server side (driver station) of the robot communications.
 */
class Server {
public:
	/**
	 * Starts a server using the default port.
	 */
	Server();

	/**
	 * Starts a server using the specified port.
	 */
	Server(int port);

	/**
	 * Joins the thread of the server to
	 * the calling thread (used in test main methods to wait for the server to finish before exiting).
	 */
	void Join();

	/**
	 * Sends a message
	 */
	int Send(Packet& packet);

	void SetMessageCallback(void (*msgCallback)(Packet&));

	inline bool IsConnected() {
		return connected;
	}

	void Disconnect();
private:
	/**
	 * The thread handling message receiving.
	 */
	Thread messageThread;

	/**
	 * The port the server is running on.
	 */
	int port;

	/**
	 * Listens for incoming connections.
	 */
	TcpListener listener;

	/**
	 * The current socket (the robot) we're connected to.
	 */
	TcpSocket connection;

	/**
	 * An event for when a packet is received.
	 */
	void (*msgCallback)(Packet&);

	bool connected;

	/**
	 * Handles all server packet receiving
	 */
	void ServerMessageLoop();

	/**
	 * Listens for an incoming connection. Returns 0 on success, 1 on error.
	 */
	int ServerListen();

	/**
	 * Accepts an incoming connection. Returns 0 on success, 1 on error.
	 */
	int ServerAccept();
};
}
#endif
