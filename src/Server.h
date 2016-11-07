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
	virtual ~Server();

	/**
	 * Joins the thread of the server to the calling thread (used in test main methods to wait for the server to finish before exiting).
	 */
	inline void Join() {
		pthread_join(mainThread, NULL);
	}

private:
	/**
	 * The main thread handling networking logic.
	 */
	pthread_t mainThread;

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
	inline void Start() {
		pthread_create(&mainThread, NULL, _ServerLoopWrapper, (void *) this);
	}

	/**
	 * A necessary helper because pthread_create doesn't like taking instance methods to start threads apparently.
	 */
	static inline void * _ServerLoopWrapper(void * server) {
		return ((Server *) server)->MainServerLoop();
	}

	/**
	 * Handles all server socket logic (accepting and listening for connections, receiving and sending packets, etc.)
	 */
	void * MainServerLoop();

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
