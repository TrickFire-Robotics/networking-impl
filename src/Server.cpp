#include "Server.h"
#include <iostream>
#include <unistd.h>
#include "Logger.h"

using namespace std;

namespace trickfire {

Server::Server() :
		port(DEFAULT_PORT) {
	Start();
}

Server::Server(int port) :
		port(port) {
	Start();
}

Server::~Server() {

}

void * Server::MainServerLoop() {
	Logger::Log(Logger::LEVEL_WARNING, "hey");

	cout << "Running server!" << endl;
	cout << "Listening!" << endl;
	if (ServerListen() != 0) {
		cerr << "Error listening on port " << port << endl;
		pthread_exit((void*) mainThread);
	}

	if (ServerAccept() != 0) {
		cerr << "Error accepting connection" << endl;
		pthread_exit((void*) mainThread);
	}

	cout << "Accepted!" << endl;

	while (true) {
		Packet received;

		if (connection.receive(received) != Socket::Done) {
			cerr << "Error receiving" << endl;
			break;
		}

		cout << "Received packet!" << endl;

		while (!received.endOfPacket()) {
			int val;
			received >> val;
			cout << val << endl;
		}
	}

	pthread_exit((void*) mainThread);
}

int Server::ServerListen() {
	if (listener.listen(port) != Socket::Done) {
		return 1;
	}
	return 0;
}

int Server::ServerAccept() {
	if (listener.accept(connection) != Socket::Done) {
		return 1;
	}
	return 0;
}
}
