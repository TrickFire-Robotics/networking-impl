#ifndef SERVER_H_
#define SERVER_H_
#define DEFAULT_PORT 25565

#include <SFML/Network.hpp>

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
	 * Joins the thread of the server to the calling thread (used in test main methods to wait for the server to finish before exiting).
	 */
	void Join();

private:
	/**
	 * The thread handling message receiving.
	 */
	pthread_t messageThread;

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
	 * Starts the server thread
	 */
	int Start();

	/**
	 * A necessary helper because pthread_create doesn't like taking instance methods to start threads apparently.
	 */
	static void * _ServerMessageLoopWrapper(void * server);

	/**
	 * Handles all server packet receiving
	 */
	void * ServerMessageLoop();

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
#endif /* SERVER_H_ */
